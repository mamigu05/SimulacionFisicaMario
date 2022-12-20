#include "Particle.h"

//Constructora de la part�cula
Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double damp, double _size, Vector4 _color, double inverse) : v(vel), a(acc), damping(damp), size(_size), inverse_mass(inverse)
{
	color = _color;
	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	force = Vector3(0, 0, 0);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)), &pose, color);
	//death = GetCurrentTime() + time;
}

//Destructora de la part�cula
Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

//M�todo que actualiza los vectores de la part�cula
void Particle::update(double t)
{
	if (inverse_mass <= 0.0f)
		return;
	pose.p += v * t;

	Vector3 totalAcceleration = a;
	totalAcceleration += force * (1 / inverse_mass);

	v += totalAcceleration * t;
	v *= powf(damping, t);

	clearForce();
	/*pose = physx::PxTransform(pose.p.x + v.x * t, pose.p.y + v.y * t, pose.p.z + v.z * t);
	v += a * t;
	v *= powf(damping, t);*/
}

//M�todo que asigna un color a la part�cula
void Particle::setColor(Vector4 _color)
{
	renderItem->color = _color;
}

void ParticleSystem::update(double t, int i)
{
	timer++;
	if (i == 0)
	{
		v = Vector3((rand() % 50 - 25), (rand() % 50 - 25), 25);

		_particles.push_back(new Particle(posicion, v, Vector3(0, -9.8, 0), 0.99, 0.75, color, 1));

		for (Particle* p : _particles)
		{
			p->update(t);
			if (p->pose.p.z > posicion.z + 40)
				_particlesToDelete.emplace_back(p);
		}
	}

	if (i == 1)
	{
		if (timer < 40)
		{
			v = Vector3((rand() % 50 - 25), 25, (rand() % 50 - 25));
			_particles.push_back(new Particle(posicion, v, Vector3(0, -9.8, 0), 0.99, 0.75, color, 1));
		}
		for (Particle* p : _particles)
		{
			p->update(t);
			if (p->pose.p.y > posicion.y + 20)
				_particlesToDelete.emplace_back(p);
		}
		
	}

	for (Particle* p : _particlesToDelete) {
		_particles.remove(p);
		delete p;
	}

	_particlesToDelete.clear();
}

bool Firework::update(double t)
{
	Particle::update(t);
	age -= t;
	return (age < 0);
}

void Fireworks::createFireworkRules()
{
	//Se inicializa el vector
	for (int i = 0; i < 3; i++)
		rules.push_back(new FireworkRule());

	//Ceniza
	rules[0]->setParameters(0, 3, 6, Vector3(-1, -10, -1), Vector3(1, 10, 1), 0.8, Payload(1, 1));
	//Cohete
	rules[1]->setParameters(1, 2, 4, Vector3(0, 100, 0), Vector3(0, 170, 0), 0.99, Payload(2, 105));
	//Explosi�n
	rules[2]->setParameters(2, 1, 3, Vector3(-60, -60, -60), Vector3(60, 60, 60), 0.5, Payload(0, 2));

	createFirework();
}

Firework* Fireworks::allocNewFirework()
{
	Firework* newFirework = new Firework();
	fireworks.push_back(newFirework);
	return newFirework;
}

void Fireworks::deleteFireworks()
{
	fireworks.erase(remove_if(fireworks.begin(), fireworks.end(), [](const Firework* f)
		{
			if (f->isActive())
				return false;
			else
			{
				delete f;
				return true;
			}
		}), fireworks.end());
}

void Fireworks::fireworksCreate(Payload p, const Firework* parent)
{
	FireworkRule* rule = getRuleFromType(p.type);
	for (int i = 0; i < p.count; i++)
	{
		Firework* newFirework = allocNewFirework();
		rule->create(newFirework, p, parent);
	}
}

void Fireworks::fireworksUpdate(double t)
{
	for (int i = 0; i < fireworks.size(); i++)
	{
		if (fireworks[i]->isActive())
		{
			if (fireworks[i]->update(t))
			{
				FireworkRule* rule = getRuleFromType(fireworks[i]->type);
				fireworks[i]->setInactive();
				for (Payload payload : rule->payloads)
					if (payload.type != 1)
						fireworksCreate(payload, fireworks[i]);
			}
		}
	}
	deleteFireworks();
}

void Forces::update(double t)
{
	if (timer > 30)
	{
		Vector3 pos;
		Vector4 color;
		if (type == 0)
		{
			pos = Vector3(-10, 0, 0);
			color = Vector4(0, 0, 1, 1);
		}
		else if (type == 1)
		{
			pos = Vector3(0, 0, 0);
			color = Vector4(1, 0, 0, 1);
		}
		else if (type == 2)
		{
			pos = Vector3(10, 0, 0);
			color = Vector4(1, 0.8, 0, 1);
		}
		else if (type == 3)
		{
			pos = Vector3((float)(rand() % 800) - 400, -5, (float)(rand() % 800) - 400);
			color = Vector4(1, 1, 1, 1);
		}
		particles.push_back(new Particle(pos, Vector3(0, 10, 0), Vector3(0, 0, 0), 0.99, 1.0, color, 2));
		timer = 0;
	}

	for (Particle* p : particles)
	{
		p->update(t);
		if (p->pose.p.y < -10 || p->pose.p.y > 1000)
			particlesToDelete.push_back(p);
	}

	for (Particle* p : particlesToDelete) {
		p->deleteReg = true;
		particles.remove(p);
		delete p;
	}

	timer++;
	particlesToDelete.clear();
}
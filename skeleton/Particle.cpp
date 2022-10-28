#include "Particle.h"

//Constructora de la partícula
Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double damp, double _size, Vector4 _color, double inverse) : v(vel), a(acc), damping(damp), size(_size), inverse_mass(inverse)
{
	color = _color;
	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)), &pose, color);
	//death = GetCurrentTime() + time;
}

//Destructora de la partícula
Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

//Método que actualiza los vectores de la partícula
void Particle::update(double t)
{
	pose = physx::PxTransform(pose.p.x + v.x * t, pose.p.y + v.y * t, pose.p.z + v.z * t);
	v += a * t;
	v *= powf(damping, t);
}

//Método que asigna un color a la partícula
void Particle::setColor(Vector4 _color)
{
	renderItem->color = _color;
}

ParticleSystem::ParticleSystem()
{

}

void ParticleSystem::update(double t)
{
	v = Vector3((rand() % 50 - 25), 25, (rand() % 50 - 25));

	_particles.push_back(new Particle(Vector3(0.0, 0.0, 0.0), v, Vector3(0, -9.8, 0), 0.99, 1.0, { 1.0, 1.0, 0.0, 1.0 }, 0));

	for (Particle* p : _particles) {
		p->update(t);
		if (p->pose.p.y < -20)
			_particlesToDelete.emplace_back(p);
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
	rules[0]->setParameters(0, 5, 8, 0.8, 2, 0.99, Payload(1, 1));
	//Cohete
	rules[1]->setParameters(1, 1, 3, 0.99, 10, 0.99, Payload(2, 35));
	//Explosión
	rules[2]->setParameters(2, 1, 3, 0.5, -5, 0.99, Payload(0, 1));

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
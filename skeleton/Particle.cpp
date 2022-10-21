#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double damp, double size, Vector4 color, double time)
{
	v = vel;
	a = acc;
	damping = damp;
	_remaining_time = time;

	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)), &pose, color);
	death = GetCurrentTime() + time;
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::update(double t)
{
	pose = physx::PxTransform(pose.p.x + v.x * t, pose.p.y + v.y * t, pose.p.z + v.z * t);
	v += a * t;
	v *= powf(damping, t);
}

ParticleSystem::ParticleSystem()
{

}

void ParticleSystem::update(double t)
{
	v = Vector3((rand() % 50 - 25), 25, (rand() % 50 - 25));

	_particles.push_back(new Particle(Vector3(0.0, 0.0, 0.0), v, Vector3(0, -9.8, 0), 0.99, 1.0, { 1.0, 1.0, 0.0, 1.0 }, 25));

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

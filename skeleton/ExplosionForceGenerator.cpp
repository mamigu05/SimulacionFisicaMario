#include "ExplosionForceGenerator.h"
#include "Particle.h"

ExplosionForceGenerator::ExplosionForceGenerator(Vector3 _force, Vector3 _center, double _ratio) : force(_force), center(_center), ratio(_ratio)
{
	p = physx::PxTransform(_center);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(ratio)), &p, Vector4(0, 0, 1, 0.1));
}

ExplosionForceGenerator::~ExplosionForceGenerator()
{
	delete renderItem;
	renderItem = nullptr;
}

void ExplosionForceGenerator::updateForce(Particle* particle, double t)
{
	if (!particle->hasFiniteMass())
		return;
	Vector3 pos = particle->pose.p;
	if (distance(particle))
	{
		Vector3 vel = pos - center;
		double distance = abs(sqrt(powf(pos.x - center.x, 2) + powf(pos.y - center.y, 2) + powf(pos.z - center.z, 2)));
		particle->addForce({ Vector3(vel * force.x * (1 - distance / ratio)) });
	}
	else
		particle->clearForce();
}

bool ExplosionForceGenerator::distance(Particle* particle)
{
	Vector3 pos = particle->pose.p;
	Vector3 distance = Vector3(center.x - pos.x, center.y - pos.y, center.z - pos.z);
	return (distance.x < ratio&& distance.y < ratio&& distance.z < ratio);
}
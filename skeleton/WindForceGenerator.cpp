#include "WindForceGenerator.h"
#include "Particle.h"

WindForceGenerator::WindForceGenerator(Vector3 _force, Vector3 _center, double _ratio) : force(_force), center(_center), ratio(_ratio)
{
	p = physx::PxTransform(_center);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(ratio)), &p, Vector4(0, 0, 1, 0.1));
}

WindForceGenerator::~WindForceGenerator()
{
	delete renderItem;
	renderItem = nullptr;
}

void WindForceGenerator::updateForce(Particle* particle, double t)
{
	if (!particle->hasFiniteMass())
		return;
	if (distance(particle))
		particle->addForce({ force });
	else
		particle->clearForce();
}

bool WindForceGenerator::distance(Particle* particle)
{
	Vector3 pos = particle->pose.p;
	Vector3 distance = Vector3(center.x - pos.x, center.y - pos.y, center.z - pos.z);
	return (distance.x < ratio&& distance.y < ratio&& distance.z < ratio);
}

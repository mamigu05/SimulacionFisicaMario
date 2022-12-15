#include "RBExplosionForceGenerator.h"

RBExplosionForceGenerator::RBExplosionForceGenerator(Vector3 _force, Vector3 _center, double _ratio) : force(_force), center(_center), ratio(_ratio)
{
	p = physx::PxTransform(_center);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(ratio)), &p, Vector4(0, 0, 1, 0.1));
}

RBExplosionForceGenerator::~RBExplosionForceGenerator()
{
	delete renderItem;
	renderItem = nullptr;
}

void RBExplosionForceGenerator::updateForce(RB* rb, double t)
{
	Vector3 pos = rb->rDynamic->getGlobalPose().p;
	if (distance(rb))
	{
		Vector3 vel = pos - center;
		double distance = abs(sqrt(powf(pos.x - center.x, 2) + powf(pos.y - center.y, 2) + powf(pos.z - center.z, 2)));
		rb->force = Vector3{ Vector3(vel * force.x * (1 - distance / ratio)) };
	}
	else
		rb->force = { 0, 0, 0 };
}

bool RBExplosionForceGenerator::distance(RB* rb)
{
	Vector3 pos = rb->rDynamic->getGlobalPose().p;
	Vector3 distance = Vector3(center.x - pos.x, center.y - pos.y, center.z - pos.z);
	return (distance.x < ratio&& distance.y < ratio&& distance.z < ratio);
}
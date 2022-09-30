#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double damp, double size, Vector4 color)
{
	v = vel;
	a = acc;
	damping = damp;

	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)), &pose, color);
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
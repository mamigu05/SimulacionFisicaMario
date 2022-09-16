#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double damp)
{
	v = vel;
	a = acc;
	damping = damp;

	pose = physx::PxTransform(pos.x, pos.y, pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, { 1, 1, 1, 1 });
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::update(double t)
{
	pose = physx::PxTransform(pose.p.x + v.x * t, pose.p.y + v.y * t, pose.p.z + v.z * t);
}

void Particle::integrate(double t)
{
	p += v * t;
	v += a * t;
	v *= powf(damping, t);
}
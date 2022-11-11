#include "GravityForceGenerator.h"
#include "Particle.h"

void GravityForceGenerator::updateForce(Particle* p, double t)
{
	if (!p->hasFiniteMass())
		return;
	p->addForce(_gravity * p->getMass());
}
#include "ParticleForceRegistry.h"
#include "Particle.h"
#include <iostream>

void ParticleForceRegistry::updateForces(double t)
{
	for (auto it = begin(); it != end(); ++it)
	{
		it->first->updateForce(it->second, t);
		if (it->second->deleteReg) {
			it = erase(it);
		}
	}
}

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, Particle* p, int type)
{
	this->insert(FRPair(fg, p));
	if (type == GRAVITY)
		p->gravity = true;
	if (type == WIND)
		p->wind = true;
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p)
{
	for (auto it = begin(); it != end(); ++it)
		erase(it);
	this->clear();
}
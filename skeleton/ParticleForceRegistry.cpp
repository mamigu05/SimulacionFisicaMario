#include "ParticleForceRegistry.h"
#include "Particle.h"
#include <iostream>

void ParticleForceRegistry::updateForces(double t)
{
	for (auto it = begin(); it != end(); ++it)
		it->first->updateForce(it->second, t);
}

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, Particle* p)
{
	this->insert(FRPair(fg, p));
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p)
{
	for (auto it = begin(); it != end(); ++it)
		erase(it);
	this->clear();
}
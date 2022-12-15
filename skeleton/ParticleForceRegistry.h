#pragma once
#include <map>
#include "ForceGenerator.h"
#include "RBForceGenerator.h"

const enum { GRAVITY, WIND, EXPLOSION2 };

typedef std::pair<ForceGenerator*, Particle*> FRPair;

class ParticleForceRegistry : public std::multimap<ForceGenerator*, Particle*>
{
public:
	void updateForces(double duration);
	void addRegistry(ForceGenerator* fg, Particle* p, int type);
	void deleteParticleRegistry(Particle* p);
};
#pragma once
#include <map>
#include "ForceGenerator.h"

const enum { GRAVITY, WIND };

typedef std::pair<ForceGenerator*, Particle*> FRPair;

class ParticleForceRegistry : public std::multimap<ForceGenerator*, Particle*>
{
public:
	void updateForces(double duration);
	void addRegistry(ForceGenerator* fg, Particle* p, int type);
	void deleteParticleRegistry(Particle* p);
};
#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(double h, double v, double d);
	virtual void updateForce(Particle* particle, double t);
	~BuoyancyForceGenerator();
protected:
	double height, volume, density, gravity = 9.8;
	Particle* liquid_particle;
};


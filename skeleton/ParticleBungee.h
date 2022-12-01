#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class ParticleBungee : ForceGenerator
{
public:
	ParticleBungee(double _k, double _resting_length, Particle* _other) : k(_k), resting_length(_resting_length), other(_other) {}
	virtual void updateForce(Particle* particle, double t);
protected:
	Particle* other;
	double k, resting_length;
};


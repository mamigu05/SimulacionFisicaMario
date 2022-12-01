#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double _k, double _resting_length, Particle* _other) : k(_k), resting_length(_resting_length), other(_other) {};
	virtual void updateForce(Particle* particle, double t);
	inline void setK(double _k) { k = _k; }
	void addK() { k++; }
	void subK() { k--; }
protected:
	double k;
	double resting_length;
	Particle* other;
};

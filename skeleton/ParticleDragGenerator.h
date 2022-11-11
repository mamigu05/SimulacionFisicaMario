#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class ParticleDragGenerator : public ForceGenerator
{
public:
	ParticleDragGenerator(const double k1, const double k2) : _k1(k1), _k2(k2) {}
	virtual void updateForce(Particle* particle, double t);
	inline void setDrag(double k1, double k2) { _k1 = k1; _k2 = k2; }
	inline double getK1() { return _k1; }
	inline double getK2() { return _k2; }
protected:
	double _k1, _k2;
};


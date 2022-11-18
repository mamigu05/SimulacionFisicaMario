#pragma once
#include "WindForceGenerator.h"

class WhirlwindForceGenerator : public WindForceGenerator
{
public:
	WhirlwindForceGenerator() : WindForceGenerator(Vector3(-50, 0, 0), Vector3(0, 50, 0), 20.0) {};
	void updateForce(Particle* particle, double t);
};


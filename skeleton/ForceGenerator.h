#pragma once
#include <string>

class Particle;
class ForceGenerator
{
public:
	virtual void updateForce(Particle* particle, double duration) = 0;
	std::string _name;
	double t = -1e10;
};
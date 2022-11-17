#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "ForceGenerator.h"

class WindForceGenerator : public ForceGenerator
{
public:
	const Vector3 force, center;
	physx::PxTransform p;
	RenderItem* renderItem;
	double ratio;

	WindForceGenerator(Vector3 _force, Vector3 _center, double _ratio);
	~WindForceGenerator();
	void updateForce(Particle* particle, double t);
	bool distance(Particle* particle);
};


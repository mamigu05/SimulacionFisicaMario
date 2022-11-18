#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "ForceGenerator.h"

class ExplosionForceGenerator : public ForceGenerator
{
public:
	const Vector3 force, center;
	physx::PxTransform p;
	RenderItem* renderItem;
	double ratio;

	ExplosionForceGenerator(Vector3 _force, Vector3 _center, double _ratio);
	~ExplosionForceGenerator();
	void updateForce(Particle* particle, double t);
	bool distance(Particle* particle);
};


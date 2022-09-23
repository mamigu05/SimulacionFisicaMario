#pragma once

#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, double damping);
	~Particle();

	void update(double t);
private:
	Vector3 v;
	Vector3 p;
	Vector3 a;

	double damping;
	physx::PxTransform pose;
	RenderItem* renderItem;
};


#pragma once

#include "RenderUtils.hpp"

class Particle
{
private:
	physx::PxTransform pose;
	RenderItem* renderItem;

	Vector3 v;
	Vector3 a;

	double damping;
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, double damping, double size, Vector4 color);
	~Particle();

	void update(double t);
};


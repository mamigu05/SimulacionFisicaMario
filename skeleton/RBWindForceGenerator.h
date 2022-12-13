#pragma once
#include "RBForceGenerator.h"

class RBWindForceGenerator : public RBForceGenerator
{
	Vector3 wind;
public:
	RBWindForceGenerator(const Vector3 _wind) : wind(_wind) {}
	~RBWindForceGenerator() {}
	virtual void updateForce(RB* body, double t);
};


#pragma once

#include "RBForceGenerator.h"

class RBTorqueForceGenerator : public RBForceGenerator
{
	Vector3 torque;
public:
	RBTorqueForceGenerator(const Vector3 _torque) : torque(_torque) {}
	~RBTorqueForceGenerator() {}
	virtual void updateForce(RB* body, double t);
};


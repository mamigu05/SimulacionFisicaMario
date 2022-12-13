#pragma once
#include "RBSystem.h"

class RBForceGenerator
{
public:
	virtual void updateForce(RB* body, double t) = 0;
};


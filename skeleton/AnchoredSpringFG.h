#pragma once

#include "SpringForceGenerator.h"
#include "core.hpp"

class AnchoredSpringFG : public SpringForceGenerator
{
public:
	AnchoredSpringFG(double k, double resting, Vector3& anchor_pos);
	~AnchoredSpringFG();
};

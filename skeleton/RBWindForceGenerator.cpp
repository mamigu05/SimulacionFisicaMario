#include "RBWindForceGenerator.h"

void RBWindForceGenerator::updateForce(RB* body, double t)
{
	body->force += wind;
}
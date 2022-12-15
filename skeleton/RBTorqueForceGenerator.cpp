#include "RBTorqueForceGenerator.h"

void RBTorqueForceGenerator::updateForce(RB* body, double t)
{
	body->torque += torque;
}
#include "SpringForceGenerator.h"
#include "Particle.h"

void SpringForceGenerator::updateForce(Particle* particle, double t)
{
	Vector3 force = other->pose.p - particle->pose.p;

	const double length = force.normalize();
	const double delta_x = length - resting_length;

	force *= delta_x * k;

	particle->addForce(force);
}

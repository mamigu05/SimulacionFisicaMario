#include "WhirlwindForceGenerator.h"
#include "Particle.h"

void WhirlwindForceGenerator::updateForce(Particle* particle, double t)
{
	double k = 5;
	Vector3 veloc = k * Vector3(10 - (particle->pose.p.z), 50 - (particle->pose.p.y),  5 - (particle->pose.p.x));

	Vector3 v = particle->pose.p - veloc;
	double mod = v.normalize();
	mod = 3 * mod + 0 * powf(mod, 2);
	if (WindForceGenerator::distance(particle))
		particle->addForce(-v * mod);
}
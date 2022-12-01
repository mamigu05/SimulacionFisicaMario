#include "ParticleBungee.h"
#include "Particle.h"

void ParticleBungee::updateForce(Particle* particle, double t)
{
	Vector3 f = particle->pose.p;
	f -= other->pose.p;

	double length = f.normalize();
	length -= resting_length;
	if (length <= 0.0f)
		return;

	f *= -(length * k);
	particle->addForce(f);
}
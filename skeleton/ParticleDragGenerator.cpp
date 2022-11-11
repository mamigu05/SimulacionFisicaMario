#include "ParticleDragGenerator.h"
#include "Particle.h"

void ParticleDragGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getMass() < 1e-10))
		return;

	Vector3 v = particle->v;
	double drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;
	particle->addForce(dragF);
}
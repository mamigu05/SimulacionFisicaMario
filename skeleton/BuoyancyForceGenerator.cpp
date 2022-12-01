#include "BuoyancyForceGenerator.h"
#include "Particle.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(double h, double v, double d) : height(h), volume(v), density(d)
{
	liquid_particle = new Particle({ 10, 40, 10 }, { 0, 0, 0 }, { 0, 0, 0 }, 0, 1, { 1.0, 0.0, 0.0, 1 }, 1);
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
	delete liquid_particle;
}

void BuoyancyForceGenerator::updateForce(Particle* particle, double t)
{
	double h = particle->pose.p.y;
	double h0 = liquid_particle->pose.p.y;

	Vector3 f(0, 0, 0);
	double immersed = 0.0;
	if (h - h0 > height * 0.5)
		immersed = 0.0;
	else if (h - h0 > height * 0.5)
		immersed = 1.0;
	else
		immersed = (h0 - h) / height + 0.5;
	f.y = density * volume * immersed * gravity;

	particle->addForce(f);
}
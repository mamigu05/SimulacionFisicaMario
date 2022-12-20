#include "BuoyancyForceGenerator.h"
#include "Particle.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(double h, double v, double d) : height(h), volume(v), density(d)
{
	//liquid_particle = new Particle({ 10, 30, 10 }, { 0, 0, 0 }, { 0, 0, 0 }, 0, 1, { 1.0, 0.0, 0.0, 1 }, 1);
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
	//delete liquid_particle;
}

void BuoyancyForceGenerator::updateForce(Particle* particle, double t)
{
	/*double h = particle->pose.p.y;
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

	particle->addForce(f);*/
	float depth;
	depth = particle->pose.p.y;
	Vector3 f(0.0f, 0.0f, 0.0f);
	if (depth > (density + height)) {
		//p->setColor({ 1,0,0,1 });
		return;
	}
	if (depth < (density - height)) {
		//p->setColor({ 1,0,1,1 });
		f.y = 1000.0f * volume * 10.0f;
	}
	else {
		float depthExt = density + height;
		float volFactor = (depthExt - depth) / (2 * height);
		f.y = 1000.0f * volume * volFactor * 10.0f;
		//p->setColor({ 0.5,0,1,1 });
	}
	particle->addForce(f);
}
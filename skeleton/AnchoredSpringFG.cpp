#include "AnchoredSpringFG.h"
#include "Particle.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting, Vector3& anchor_pos) : SpringForceGenerator(k, resting, nullptr)
{
	other = new Particle(anchor_pos, { 0, 0, 0 }, { 0, 0, 0 }, 0, 1, { 1.0, 0.0, 0.0, 1 }, 1e6);
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete other;
}
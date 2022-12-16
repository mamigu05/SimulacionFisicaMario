#pragma once
#include "RBForceGenerator.h"

//Clase que simula un viento que afecta a sólidos rígidos
class RBWindForceGenerator : public RBForceGenerator
{
	Vector3 wind;
public:
	RBWindForceGenerator(const Vector3 _wind) : wind(_wind) {}
	~RBWindForceGenerator() {}
	virtual void updateForce(RB* body, double t);
};


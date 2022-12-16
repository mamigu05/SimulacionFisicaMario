#pragma once
#include "RBForceGenerator.h"

//Clase que simula una explosión que afecta a sólidos rígidos
class RBExplosionForceGenerator : public RBForceGenerator
{
public:
	const Vector3 force, center;
	physx::PxTransform p;
	RenderItem* renderItem;
	double ratio;

	RBExplosionForceGenerator(Vector3 _force, Vector3 _center, double _ratio);
	~RBExplosionForceGenerator();
	void updateForce(RB* rb, double t);
	bool distance(RB* rb);
};


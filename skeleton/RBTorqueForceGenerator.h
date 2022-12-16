#pragma once

#include "RBForceGenerator.h"

//Clase que se encarga de la rotación del cuerpo causada por su momento
class RBTorqueForceGenerator : public RBForceGenerator
{
	Vector3 torque;
public:
	RBTorqueForceGenerator(const Vector3 _torque) : torque(_torque) {}
	~RBTorqueForceGenerator() {}
	virtual void updateForce(RB* body, double t);
};


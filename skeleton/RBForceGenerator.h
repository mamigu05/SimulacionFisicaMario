#pragma once
#include "RBSystem.h"

//Clase que sirve como generador de fuerzas de sólidos rígidos
class RBForceGenerator
{
public:
	virtual void updateForce(RB* body, double t) = 0;
};


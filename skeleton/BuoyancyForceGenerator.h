#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

//Clase que aplica una fuerza de flotación
class BuoyancyForceGenerator : public ForceGenerator
{
public:
	//Constructora de la clase
	BuoyancyForceGenerator(double h, double v, double d);
	//Método que actualiza los valores de la fuerza
	virtual void updateForce(Particle* particle, double t);
	//Destructora de la clase
	~BuoyancyForceGenerator();
protected:
	double height, volume, density, gravity = 9.8;
	Particle* liquid_particle;
};


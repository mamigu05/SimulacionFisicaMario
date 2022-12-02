#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

//Clase que aplica una fuerza elástica
class SpringForceGenerator : public ForceGenerator
{
public:
	//Constructora de la clase
	SpringForceGenerator(double _k, double _resting_length, Particle* _other) : k(_k), resting_length(_resting_length), other(_other) {};
	//Método que actualiza los valores de la fuerza
	virtual void updateForce(Particle* particle, double t);
	//Método que le da un valor a k
	inline void setK(double _k) { k = _k; }
	//Método que añade valores a k
	void addK() { k++; }
	//Método que resta valores a k
	void subK() { k--; }
protected:
	//Constante elástica
	double k; 
	double resting_length;
	Particle* other;
};

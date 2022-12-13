#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

//Clase que aplica una fuerza el�stica
class SpringForceGenerator : public ForceGenerator
{
public:
	//Constructora de la clase
	SpringForceGenerator(double _k, double _resting_length, Particle* _other) : k(_k), resting_length(_resting_length), other(_other) {};
	//M�todo que actualiza los valores de la fuerza
	virtual void updateForce(Particle* particle, double t);
	//M�todo que le da un valor a k
	inline void setK(double _k) { k = _k; }
	//M�todo que a�ade valores a k
	void addK() { k++; }
	//M�todo que resta valores a k
	void subK() { k--; }
protected:
	//Constante el�stica
	double k; 
	double resting_length;
	Particle* other;
};

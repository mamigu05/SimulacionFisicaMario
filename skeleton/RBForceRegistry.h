#pragma once

#include <map>
#include "RBForceGenerator.h"

typedef std::pair<RBForceGenerator*, RB*> FRPair2;

//Clase que registra las fuerzas aplicadas a cada sólido rígido
class RBForceRegistry : public std::multimap<RBForceGenerator*, RB*>
{
public:
	void updateForces(double duration);
	void addRegistry(RBForceGenerator* rbFG, RBForceGenerator* rbFGt, RBSystem* rb);
	void deleteRBRegistry(RB* rb);
};


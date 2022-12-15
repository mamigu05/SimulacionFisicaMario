#pragma once

#include <map>
#include "RBForceGenerator.h"

typedef std::pair<RBForceGenerator*, RB*> FRPair2;

class RBForceRegistry : public std::multimap<RBForceGenerator*, RB*>
{
public:
	void updateForces(double duration);
	void addRegistry(RBForceGenerator* rbFG, RBForceGenerator* rbFGt, RBSystem* rb);
	void deleteRBRegistry(RB* rb);
};


#include "RBForceRegistry.h"
#include "RBSystem.h"
#include <iostream>

void RBForceRegistry::updateForces(double t)
{
	for (auto it = begin(); it != end(); ++it)
	{
		it->first->updateForce(it->second, t);
		if (it->second->life < 0) {
			it = erase(it);
		}
	}
}

void RBForceRegistry::addRegistry(RBForceGenerator* rbFGw, RBForceGenerator* rbFGt, RBSystem* rb)
{
	for (int i = rb->bodies.size() - 1; i >= 0; i--) {
		if (rb->bodies.at(i)->isNew) {
			this->insert(FRPair2(rbFGw, rb->bodies.at(i)));
			this->insert(FRPair2(rbFGt, rb->bodies.at(i)));
			rb->bodies.at(i)->isNew = false;
		}
	}
	/*for (auto it = rb->bodies.begin(); it != rb->bodies.end(); it++) {
		if ((*it)->isNew) {
			this->insert(FRPair2(rbFGw, (*it)));
			this->insert(FRPair2(rbFGt, (*it)));
			(*it)->isNew = false;
		}
	}*/
}

void RBForceRegistry::deleteRBRegistry(RB* rb)
{
	for (auto it = begin(); it != end(); ++it)
		erase(it);
	this->clear();
}
#include "RBSystem.h"
#include <iostream>

//Constructora de la clase con sus parámetros "set"
RBSystem::RBSystem(PxPhysics* _physics, PxScene* _scene, PxTransform _p, bool _colorRB, double _step, double _life, double _size, int _maxParticles, Vector4 _color) 
	: physics(_physics), scene(_scene), p(_p), colorRB(_colorRB), step(_step), life(_life), size(_size), maxParticles(_maxParticles), color(_color)
{
	time = 0;
	numParticles = 0;
}

//Destructora de la clase
RBSystem::~RBSystem()
{
	delete physics;
	physics = nullptr;
}

//Método que añade el sólido rígido al mundo
void RBSystem::addBody()
{
	if (colorRB) {
		color = Vector4(float((rand() % 10) / 10.0), float((rand() % 10) / 10.0), float((rand() % 10) / 10.0), 1.0);
	}

	RB* body = nullptr;
	body = new RB;

	PxRigidDynamic* new_solid;
	new_solid = physics->createRigidDynamic(p);
	PxShape* shape = CreateShape(PxBoxGeometry(size, size, size));
	new_solid->attachShape(*shape);
	Vector3 vel = { -5.0f + rand() / RAND_MAX / (10.0f),-5.0f + rand() / RAND_MAX / (10.0f) ,-5.0f + rand() / RAND_MAX / (10.0f) };
	new_solid->setLinearVelocity(vel);
	new_solid->setLinearDamping(0.0);
	new_solid->setAngularVelocity({ 0, 0, 0 });
	new_solid->setAngularDamping(0.05);
	
	PxRigidBodyExt::updateMassAndInertia(*new_solid, 10);
	scene->addActor(*new_solid);

	//Se asignan los parámetros al rb
	body->rDynamic = new_solid;
	body->isNew = true;
	body->life = life;
	body->force = { 0.0, 100.0, 0.0 };
	body->torque = { 0.0f, 0.0f, 0.0f };
	body->ri = new RenderItem(shape, new_solid, color);
	bodies.push_back(body);
	numParticles++;
	time = 0;
}

//Update del rb
void RBSystem::update(double t)
{
	//Determinado un tiempo, se añade un nuevo rb
	time += t;
	if (time > step && numParticles < maxParticles)
		addBody();

	if (!bodies.empty()) {
		for (auto it = bodies.begin(); it != bodies.end(); ++it) {
			(*it)->rDynamic->addForce((*it)->force, PxForceMode::eFORCE);
			(*it)->force = { 0.0f, 0.0f, 0.0f };

			//Torque del rb
			(*it)->rDynamic->addTorque((*it)->torque);
			(*it)->torque = { 0.0f, 0.0f, 0.0f };

			(*it)->life -= t;
			//Si la vida llega a su fin, se elimina
			if ((*it)->life < 0) it = remove(it);
		}
	}
}

std::vector<RB*>::iterator RBSystem::remove(std::vector<RB*>::iterator it) {
	numParticles--;
	DeregisterRenderItem((*it)->ri);
	scene->removeActor(*(*it)->rDynamic);
	return bodies.erase(it);
}
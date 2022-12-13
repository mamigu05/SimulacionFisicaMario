#include "RBSystem.h"

RBSystem::RBSystem(PxPhysics* _physics, PxScene* _scene, PxTransform _p, bool _colorRB, double _step, double _life, double _size, int _maxParticles, Vector4 _color) 
	: physics(_physics), scene(_scene), p(_p), colorRB(_colorRB), step(_step), life(_life), size(_size), maxParticles(_maxParticles), color(_color)
{
	time = 0;
	numParticles = 0;
}

void RBSystem::addBody()
{
	RB* body = nullptr;
	body = new RB;

	PxRigidDynamic* new_solid;
	new_solid = physics->createRigidDynamic(PxTransform(p));
	new_solid->setLinearVelocity(vel);
	new_solid->setAngularVelocity({ 0, 0, 0 });
	PxShape* shape = CreateShape(PxBoxGeometry(size, size, size));
	new_solid->attachShape(*shape);
	new_solid->setMassSpaceInertiaTensor({ size * size, size * size, size * size });
	scene->addActor(*new_solid);

	body->rDynamic = new_solid;
	body->isNew = true;
	body->life = life;
	body->force = { 0.0f, 0.0f, 0.0f };
	body->ri = new RenderItem(shape, new_solid, color);
	bodies.push_back(body);
	numParticles++;
	time = 0;
}
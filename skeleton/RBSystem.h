#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;


struct RB
{
	PxRigidDynamic* rDynamic = nullptr;
	RenderItem* ri = nullptr;
	PxVec3 force;
	PxVec3 torque;
	double life;
	bool isNew;
};

class RBSystem
{
private:
	PxScene* scene;
	PxPhysics* physics;
	PxTransform p;
	Vector4 color;
	bool colorRB;
	double step, size, time, life;
	int numParticles, maxParticles;
	std::vector<RB*>::iterator remove(std::vector<RB*>::iterator it);

public:
	RBSystem(PxPhysics* _physics, PxScene* _scene, PxTransform _p, bool _colorRB = true, double _step = 1.5, double _life = 15, double _size = 1, int _maxParticles = 10, Vector4 _color = { 1, 0, 0, 1.0 });
	~RBSystem();
	void addBody();
	void update(double t);
	std::vector<RB*> bodies;
};


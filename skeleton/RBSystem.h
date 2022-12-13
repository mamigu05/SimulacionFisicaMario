#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;


struct RB
{
	PxRigidDynamic* rDynamic = nullptr;
	RenderItem* ri = nullptr;
	PxVec3 force;
	double life;
	bool isNew;
};

class RBSystem
{
private:
	PxTransform p;
	PxScene* scene;
	PxPhysics* physics;
	Vector4 color;
	bool colorRB;
	double step, size, time, life;
	int numParticles, maxParticles;

public:
	RBSystem(PxPhysics* _physics, PxScene* _scene, PxTransform _p, bool _colorRB, double _step, double _life, double _size, int _maxParticles, Vector4 _color);
	~RBSystem();
	void addBody();
	std::vector<RB*> bodies;
};


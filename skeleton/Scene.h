#pragma once
#include "core.hpp"
#include "Particle.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"
#include "WindForceGenerator.h"

class Scene
{
private:
	GravityForceGenerator* gravityB;
	GravityForceGenerator* gravityR;
	GravityForceGenerator* gravityY;
	WindForceGenerator* wind;
	Forces* forceB;
	Forces* forceR;
	Forces* forceY;

	int scene;
public:
	ParticleForceRegistry* pFReg;

	Scene();
	~Scene();
	void createScene1();
	void createScene2();
	void createScene3();
	void update(double t);
};


#pragma once
#include "core.hpp"
#include "Particle.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"

class Scene
{
private:
	GravityForceGenerator* gravityB;
	GravityForceGenerator* gravityR;
	GravityForceGenerator* gravityY;
	WindForceGenerator* wind;
	WhirlwindForceGenerator* whirlwind;
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
	void createScene4();
	void update(double t);
};


#pragma once
#include <iostream>
#include "core.hpp"
#include "Particle.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "BuoyancyForceGenerator.h"

class Scene
{
private:
	GravityForceGenerator* gravityB;
	GravityForceGenerator* gravityR;
	GravityForceGenerator* gravityY;
	WindForceGenerator* wind;
	WhirlwindForceGenerator* whirlwind;
	ExplosionForceGenerator* explosion;
	Forces* forceB;
	Forces* forceR;
	Forces* forceY;
	Particle* p1;
	AnchoredSpringFG* asForce;

	int scene;
	bool force;
public:
	ParticleForceRegistry* pFReg;

	Scene();
	~Scene();
	void createScene1();
	void createScene2();
	void createScene3();
	void createScene4();
	void createScene5();
	void createScene6();
	void createScene7();
	void createScene8();
	void update(double t);
	void addK() { if (scene == 6) asForce->addK();}
	void subK() { if (scene == 6) asForce->subK(); }
	double askK();
	int getScene() { return scene; };
};


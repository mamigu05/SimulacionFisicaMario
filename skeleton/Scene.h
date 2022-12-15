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
#include "RBSystem.h"
#include "RBTorqueForceGenerator.h"
#include "RBWindForceGenerator.h"
#include "RBExplosionForceGenerator.h"
#include "RBForceRegistry.h"

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
	RBSystem* rbSystem;
	RBWindForceGenerator* rbWind;
	RBTorqueForceGenerator* rbTorque;
	RBExplosionForceGenerator* rbExplosion;

	int scene;
	bool force;
public:
	ParticleForceRegistry* pFReg;
	RBForceRegistry* rbFReg;

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
	void createSceneRB1(PxPhysics* _physics, PxScene* _scene);
	void createSceneRB2(PxPhysics* _physics, PxScene* _scene);
	void update(double t);
	void addK() { if (scene == 6) asForce->addK();}
	void subK() { if (scene == 6) asForce->subK(); }
	double askK();
	int getScene() { return scene; };
};


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
	ExplosionForceGenerator* explosion1;
	Forces* forceB;
	Forces* forceR;
	Forces* forceY;
	Particle* p1;
	AnchoredSpringFG* asForce;
	RBSystem* rbSystem;
	RBWindForceGenerator* rbWind;
	RBTorqueForceGenerator* rbTorque;
	RBExplosionForceGenerator* rbExplosion;
	Fireworks* fireworks;
	vector<ParticleSystem*> sonidos;

	Vector3 vBoton;

	vector<RenderItem*> platforms;
	vector<RenderItem*> bolas1;
	vector<RenderItem*> bolas2;
	vector<Particle*> muelles;
	vector<RenderItem*> cuerpos;
	vector<ParticleSystem*> blood;

	list<RenderItem*> items;
	list<RenderItem*> itemsToDelete;

	int scene;
	bool force;
	bool fuegos = false;
	bool apocalipsis = false;
public:
	ParticleForceRegistry* pFReg;
	RBForceRegistry* rbFReg;
	vector<Vector3> posCuerpos;
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
	void createFinalScene(PxPhysics* _physics, PxScene* _scene);
	void update(double t);

	void addK() { if (scene == 6) asForce->addK();}
	void subK() { if (scene == 6) asForce->subK(); }
	double askK();

	void exp() { fireworks->createFirework(); fuegos = true; }
	void addRB(PxTransform pos, Vector3 vel) { rbSystem->addBody(pos, vel); }
	void buttonPressed(Vector3 rbPos);
	void dead(Vector3 rbPos, int i);
	void apocalypse();
	void deleteBodies(int i);
	void deleteItems();
	int getScene() { return scene; };
};


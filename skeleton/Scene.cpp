#include "Scene.h"
#include "RenderUtils.hpp"

Scene::Scene()
{
	pFReg = new ParticleForceRegistry();
	gravityB = nullptr; gravityR = nullptr; gravityY = nullptr;
	wind = nullptr;
	forceB = nullptr; forceR = nullptr; forceY = nullptr;
}

Scene::~Scene()
{
	delete gravityB; gravityB = nullptr;
	delete gravityR; gravityR = nullptr;
	delete gravityY; gravityY = nullptr;
	delete wind; wind = nullptr;
	delete forceB; forceB = nullptr;
	delete forceR; forceR = nullptr;
	delete forceY; forceY = nullptr;
}

void Scene::createScene1()
{
	scene = 1;
	Particle* particle = new Particle(Vector3(10, 10, 10), Vector3(0, 2, 0), Vector3(0, 1.5, 0), 0.99, 1, Vector4(0.5, 0, 0.5, 1), 1);
	const Vector3 g = Vector3(0, 2, 0);
	GravityForceGenerator* gravity = new GravityForceGenerator(g);
	pFReg->addRegistry(gravity, particle);
}

void Scene::createScene2()
{
	scene = 2;
	forceB = new Forces(0);
	forceR = new Forces(1);
	forceY = new Forces(2);
	gravityB = new GravityForceGenerator(Vector3(0, 4, 0));
	gravityR = new GravityForceGenerator(Vector3(0, 1, 0));
	gravityY = new GravityForceGenerator(Vector3(0, 8, 0));
}

void Scene::createScene3()
{
	scene = 3;
	wind = new WindForceGenerator(Vector3(-100, 0, 0), Vector3(0, 50, 0), 20.0);
	gravityB = new GravityForceGenerator(Vector3(0, 4, 0));
	forceB = new Forces(1);
}

void Scene::update(double t)
{
	if (forceB != nullptr)
		forceB->update(t);
	if (forceR != nullptr)
		forceR->update(t);
	if (forceY != nullptr)
		forceY->update(t);
	if (scene == 2)
	{
		for (Particle* p : forceB->particles)
			if (!p->gravedad)
				pFReg->addRegistry(gravityB, p);
		for (Particle* p : forceR->particles)
			if (!p->gravedad)
				pFReg->addRegistry(gravityR, p);
		for (Particle* p : forceY->particles)
			if (!p->gravedad)
				pFReg->addRegistry(gravityY, p);
	}
	if (scene == 3)
	{
		for (Particle* p : forceB->particles) 
		{
			if (!p->gravedad) pFReg->addRegistry(gravityB, p);
			if (!p->viento) pFReg->addRegistry(wind, p);
		}
	}
}
#include "Scene.h"
#include "RenderUtils.hpp"

Scene::Scene()
{
	pFReg = new ParticleForceRegistry();
	gravityB = nullptr; gravityR = nullptr; gravityY = nullptr;
	wind = nullptr; whirlwind = nullptr; explosion = nullptr;
	forceB = nullptr; forceR = nullptr; forceY = nullptr;
}

Scene::~Scene()
{
	delete gravityB; gravityB = nullptr;
	delete gravityR; gravityR = nullptr;
	delete gravityY; gravityY = nullptr;
	delete wind; wind = nullptr;
	delete whirlwind; whirlwind = nullptr;
	delete explosion; explosion = nullptr;
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
	pFReg->addRegistry(gravity, particle, 0);
}

void Scene::createScene2()
{
	scene = 2;
	forceB = new Forces(0);
	forceR = new Forces(1);
	forceY = new Forces(2);
	gravityB = new GravityForceGenerator(Vector3(0, 1, 0));
	gravityR = new GravityForceGenerator(Vector3(0, 0.5, 0));
	gravityY = new GravityForceGenerator(Vector3(0, 1.5, 0));
}

void Scene::createScene3()
{
	scene = 3;
	wind = new WindForceGenerator(Vector3(-50, 0, 0), Vector3(0, 50, 0), 20.0);
	gravityB = new GravityForceGenerator(Vector3(0, 2, 0));
	forceB = new Forces(0);
}

void Scene::createScene4()
{
	scene = 4;
	whirlwind = new WhirlwindForceGenerator();
	gravityB = new GravityForceGenerator(Vector3(0, 2, 0));
	forceB = new Forces(0);
}

void Scene::createScene5()
{
	scene = 5;
	forceB = new Forces(0);
	explosion = new ExplosionForceGenerator(Vector3(1000, 1000, 1000), Vector3(0, 50, 0), 30.0);
}

void Scene::createScene6()
{
	//Almacena el valor de la constante del muelle
	double k = askK();

	//Cubo que se mantiene en posici�n est�tica
	physx::PxTransform* pos = new physx::PxTransform(10, -5, 10);
	RenderItem* m = new RenderItem(CreateShape(physx::PxBoxGeometry(2, 2, 2)), pos, {1, 0, 0, 1});

	//Creaci�n de la part�cula anclada al muelle
	p1 = new Particle({ 10, 45, 10 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 1, { 0.5, 0, 0.5, 1 }, 1);

	//Se crea la fuerza
	asForce = new AnchoredSpringFG(1, 10, Vector3(10, 0, 10));
	asForce->setK(k);
	//Gravedad
	gravityB = new GravityForceGenerator(Vector3(0, -3, 0));
	pFReg->addRegistry(asForce, p1, 3);
	pFReg->addRegistry(gravityB, p1, 0);
}

void Scene::createScene7()
{
	//Se crean las dos part�culas
	Particle *p1, *p2;
	p1 = new Particle({ 10.0, 45.0, 10.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 1, { 1.0, 0.0, 0.0, 1.0 }, 1);
	p2 = new Particle({ 10.0, 30.0, 10.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 1, { 1.0, 0.0, 0.0, 1.0 }, 1);
	
	//Se crean las dos fuerzas y se aplican
	SpringForceGenerator* sf1 = new SpringForceGenerator(2.0, 3.5, p2);
	pFReg->addRegistry(sf1, p1, 3);
	SpringForceGenerator* sf2 = new SpringForceGenerator(2.0, 3.5, p1);
	pFReg->addRegistry(sf2, p2, 3);

	//Se crea la gravedad que afectar� a cada part�cula
	gravityB = new GravityForceGenerator(Vector3(0, -3, 0));
	gravityY = new GravityForceGenerator(Vector3(0, 3, 0));
	pFReg->addRegistry(gravityB, p1, 0);
	pFReg->addRegistry(gravityY, p2, 0);
}

void Scene::createScene8()
{
	//Creaci�n de la part�cula
	Particle* p1;
	p1 = new Particle({ 10.0, 45.0, 10.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 1, { 1.0, 0.0, 0.0, 1.0 }, 1);

	//Representaci�n visual del agua
	physx::PxTransform* pos = new physx::PxTransform(10, 40, 10);
	RenderItem* agua = new RenderItem(CreateShape(physx::PxBoxGeometry(10, 0.1, 10)), pos, Vector4(0, 0, 0.7, 1));
	
	//Gravedad
	gravityB = new GravityForceGenerator(Vector3(0, -10, 0));

	//Fuerza de flotaci�n
	BuoyancyForceGenerator* bForce = new BuoyancyForceGenerator(15, 15, 1);
	pFReg->addRegistry(bForce, p1, 4);
	pFReg->addRegistry(gravityB, p1, 0);
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
			if (!p->gravity)
				pFReg->addRegistry(gravityB, p, 0);
		for (Particle* p : forceR->particles)
			if (!p->gravity)
				pFReg->addRegistry(gravityR, p, 0);
		for (Particle* p : forceY->particles)
			if (!p->gravity)
				pFReg->addRegistry(gravityY, p, 0);
	}
	if (scene == 3)
	{
		for (Particle* p : forceB->particles) 
		{
			if (!p->gravity) 
				pFReg->addRegistry(gravityB, p, 0);
			if (!p->wind) 
				pFReg->addRegistry(wind, p, 1);
		}
	}
	if (scene == 4)
	{
		for (Particle* p : forceB->particles)
		{
			if (!p->gravity)
				pFReg->addRegistry(gravityB, p, 0);
			if (!p->wind) 
				pFReg->addRegistry(whirlwind, p, 1);
		}
	}
	if (scene == 5) {
		for (Particle* p : forceB->particles) {
			if (!p->explosion) 
				pFReg->addRegistry(explosion, p, 2);
		}
	}
	if(scene != 5)
		pFReg->updateForces(t);
}

//M�todo que pregunta y devuelve un valor
double Scene::askK()
{
	double value;
	std::cout << "�Qu� valor quiere que tenga la constante del muelle?\n";
	cin >> value;
	return value;
}
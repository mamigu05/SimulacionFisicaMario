#include "Scene.h"
#include "RenderUtils.hpp"

Scene::Scene()
{
	pFReg = new ParticleForceRegistry();
	rbFReg = new RBForceRegistry();
	gravityB = nullptr; gravityR = nullptr; gravityY = nullptr;
	wind = nullptr; whirlwind = nullptr; explosion1 = nullptr;
	forceB = nullptr; forceR = nullptr; forceY = nullptr;
}

Scene::~Scene()
{
	delete gravityB; gravityB = nullptr;
	delete gravityR; gravityR = nullptr;
	delete gravityY; gravityY = nullptr;
	delete wind; wind = nullptr;
	delete whirlwind; whirlwind = nullptr;
	delete explosion1; explosion1 = nullptr;
	delete forceB; forceB = nullptr;
	delete forceR; forceR = nullptr;
	delete forceY; forceY = nullptr;
	delete fireworks; fireworks = nullptr;
	deleteItems();
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
	explosion1 = new ExplosionForceGenerator(Vector3(1000, 1000, 1000), Vector3(0, 50, 0), 30.0);
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

void Scene::createSceneRB1(PxPhysics* _physics, PxScene* _scene) 
{
	scene = 9;

	//Crea un suelo en la escena
	PxShape* shape = CreateShape(PxBoxGeometry(50, 1, 50));
	PxRigidStatic* ground = _physics->createRigidStatic({ 0, 0, 0 });
	ground->attachShape(*shape);
	_scene->addActor(*ground);
	RenderItem* ri = nullptr;
	ri = new RenderItem(shape, ground, { 0, 0.4, 0.7, 1 });

	//Crea un cubo como obstáculo en la escena
	PxShape* shape2 = CreateShape(PxBoxGeometry(5, 5, 5));
	PxRigidStatic* block = _physics->createRigidStatic({ -10, 5, -5 });
	block->attachShape(*shape2);
	_scene->addActor(*block);
	RenderItem* ri2 = nullptr;
	ri2 = new RenderItem(shape2, block, { 1, 0, 0.7, 1 });

	//Sistema de rb
	rbSystem = new RBSystem(_physics, _scene, PxTransform(0, 40, 10));

	rbWind = new RBWindForceGenerator({ 0.0f, 0.0f, 0.0f });
	rbTorque = new RBTorqueForceGenerator({ 1000.0f, 0.0f, 0.0f });

	forceY = new Forces(2);
	wind = new WindForceGenerator(Vector3(-100, 0, 0), Vector3(0, 25, 0), 20.0f);
	gravityB = new GravityForceGenerator(Vector3(0, 4, 0));
}

void Scene::createSceneRB2(PxPhysics* _physics, PxScene* _scene)
{
	scene = 10;
	
	//Crea un suelo en la escena
	PxShape* shape = CreateShape(PxBoxGeometry(100, 1, 100));
	PxRigidStatic* ground = _physics->createRigidStatic({ 0, 0, 0 });
	ground->attachShape(*shape);
	_scene->addActor(*ground);
	RenderItem* ri = nullptr;
	ri = new RenderItem(shape, ground, { 0.6, 0.2, 1, 1 });

	//Sistema de rb
	rbSystem = new RBSystem(_physics, _scene, PxTransform(0, 40, 0));
	rbExplosion = new RBExplosionForceGenerator(Vector3(100000, 100000, 100000), Vector3(0, 25, 0), 20.0f);
}

void Scene::createFinalScene(PxPhysics* _physics, PxScene* _scene)
{
	scene = 11;

	// -------- SUELO --------
	PxShape* shape = CreateShape(PxBoxGeometry(500, 1, 500)); 
	PxRigidStatic* ground = _physics->createRigidStatic({ 0,0,0 });
	ground->attachShape(*shape); 
	_scene->addActor(*ground);
	RenderItem* item = nullptr;
	item = new RenderItem(shape, ground, { 0.5, 0.5, 0.5, 1 });

	items.push_back(item); itemsToDelete.push_back(item);

	// -------- PLATAFORMAS ESCENARIO --------
	const physx::PxTransform* plat1 = new PxTransform(0, 0, -300);
	RenderItem* platform1 = new RenderItem(CreateShape(physx::PxBoxGeometry(200, 50, 100)), plat1, Vector4(1, 1, 1, 1));
	const physx::PxTransform* plat2 = new PxTransform(0, 0, -200);
	RenderItem* platform2 = new RenderItem(CreateShape(physx::PxBoxGeometry(50, 50, 150)), plat2, Vector4(1, 1, 1, 1));
	const physx::PxTransform* plat3 = new PxTransform(0, 53, -300);
	platforms.push_back(new RenderItem(CreateShape(physx::PxBoxGeometry(100, 3, 50)), plat3, Vector4(1, 0, 1, 1)));
	const physx::PxTransform* plat4 = new PxTransform(0, 53, -200);
	platforms.push_back(new RenderItem(CreateShape(physx::PxBoxGeometry(30, 3, 125)), plat4, Vector4(1, 0, 1, 1)));

	items.push_back(platform1); itemsToDelete.push_back(platform1);
	items.push_back(platform2); itemsToDelete.push_back(platform2);
	
	// -------- PAREDES Y TECHO ESCENARIO --------
	const physx::PxTransform* pared1 = new PxTransform(-199, 150, -300);
	RenderItem* wall1 = new RenderItem(CreateShape(physx::PxBoxGeometry(1, 100, 100)), pared1, Vector4(0.5, 0.5, 0.5, 1));
	const physx::PxTransform* pared2 = new PxTransform(199, 150, -300);
	RenderItem* wall2 = new RenderItem(CreateShape(physx::PxBoxGeometry(1, 100, 100)), pared2, Vector4(0.5, 0.5, 0.5, 1));
	const physx::PxTransform* pared3 = new PxTransform(0, 150, -400);
	RenderItem* wall3 = new RenderItem(CreateShape(physx::PxBoxGeometry(200, 100, 1)), pared3, Vector4(0.5, 0.5, 0.5, 1));
	const physx::PxTransform* techo = new PxTransform(0, 250, -300);
	RenderItem* roof = new RenderItem(CreateShape(physx::PxBoxGeometry(200, 1, 100)), techo, Vector4(0.5, 0.5, 0.5, 1));

	items.push_back(wall1); itemsToDelete.push_back(wall1);
	items.push_back(wall2); itemsToDelete.push_back(wall2);
	items.push_back(wall3); itemsToDelete.push_back(wall3);
	items.push_back(roof); itemsToDelete.push_back(roof);

	// -------- ATREZZO ESCENARIO --------

	vector<Vector4> colors;
	colors.push_back(Vector4(1, 0, 0, 1));	  
	colors.push_back(Vector4(1, 0, 1, 1));   
	colors.push_back(Vector4(0.5, 0, 1, 1)); 
	colors.push_back(Vector4(0, 0, 1, 1));   	
	colors.push_back(Vector4(0, 0.5, 1, 1)); 
	colors.push_back(Vector4(0, 1, 1, 1));   
	colors.push_back(Vector4(0, 1, 0, 1));   
	colors.push_back(Vector4(0.5, 1, 0, 1)); 
	colors.push_back(Vector4(1, 1, 0, 1));	  
	colors.push_back(Vector4(1, 0.5, 0, 1));
	
	for (int i = 0; i < 10; i++) {
		const physx::PxTransform* ball1 = new PxTransform(100 * cos((18 * i) * (3.1412 / 180)), 35 + (100 * sin((18 * i) * (3.1412 / 180))), -350);
		bolas1.push_back(new RenderItem(CreateShape(physx::PxSphereGeometry(10.0)), ball1, colors[i]));
	}

	for (int i = 60; i < 160; i += 20)
	{
		const physx::PxTransform* ball1 = new PxTransform(-110, i, -250);
		bolas2.push_back(new RenderItem(CreateShape(physx::PxSphereGeometry(10.0)), ball1, Vector4(1, 0.4, 0.7, 1)));
	}

	for (int i = 60; i < 160; i += 20)
	{
		const physx::PxTransform* ball1 = new PxTransform(110, i, -250);
		bolas2.push_back(new RenderItem(CreateShape(physx::PxSphereGeometry(10.0)), ball1, Vector4(1, 0.4, 0.7, 1)));
	}

	// MICRÓFONO
	const physx::PxTransform* soporte = new PxTransform(0, 75, -85);
	RenderItem* support = new RenderItem(CreateShape(physx::PxBoxGeometry(1.5, 20, 1.5)), soporte, Vector4(0.5, 0.5, 0.5, 1));
	const physx::PxTransform* microfono = new PxTransform(0, 98, -87);
	RenderItem* microphone = new RenderItem(CreateShape(physx::PxSphereGeometry(3.5)), microfono, Vector4(0.1, 0.1, 0.1, 1));

	items.push_back(support); itemsToDelete.push_back(support);
	items.push_back(microphone); itemsToDelete.push_back(microphone);

	// ALTAVOCES
	const physx::PxTransform* altavoz1 = new PxTransform(-160, 90, -250);
	RenderItem* speaker1 = new RenderItem(CreateShape(physx::PxBoxGeometry(20, 40, 20)), altavoz1, Vector4(0.5, 0.5, 0.5, 1));
	const physx::PxTransform* bolaAltavoz1 = new PxTransform(-160, 110, -230);
	RenderItem* ballSpeaker1 = new RenderItem(CreateShape(physx::PxSphereGeometry(15)), bolaAltavoz1, Vector4(0.1, 0.1, 0.1, 0));
	const physx::PxTransform* bolaAltavoz2 = new PxTransform(-160, 70, -230);
	RenderItem* ballSpeaker2 = new RenderItem(CreateShape(physx::PxSphereGeometry(15)), bolaAltavoz2, Vector4(0.1, 0.1, 0.1, 0));
	const physx::PxTransform* altavoz2 = new PxTransform(160, 90, -250);
	RenderItem* speaker2 = new RenderItem(CreateShape(physx::PxBoxGeometry(20, 40, 20)), altavoz2, Vector4(0.5, 0.5, 0.5, 1));
	const physx::PxTransform* bolaAltavoz3 = new PxTransform(160, 110, -230);
	RenderItem* ballSpeaker3 = new RenderItem(CreateShape(physx::PxSphereGeometry(15)), bolaAltavoz3, Vector4(0.1, 0.1, 0.1, 0));
	const physx::PxTransform* bolaAltavoz4 = new PxTransform(160, 70, -230);
	RenderItem* ballSpeaker4 = new RenderItem(CreateShape(physx::PxSphereGeometry(15)), bolaAltavoz4, Vector4(0.1, 0.1, 0.1, 0));

	items.push_back(speaker1); itemsToDelete.push_back(speaker1);
	items.push_back(speaker2); itemsToDelete.push_back(speaker2);
	items.push_back(ballSpeaker1); itemsToDelete.push_back(ballSpeaker1);
	items.push_back(ballSpeaker2); itemsToDelete.push_back(ballSpeaker2);
	items.push_back(ballSpeaker3); itemsToDelete.push_back(ballSpeaker3);
	items.push_back(ballSpeaker4); itemsToDelete.push_back(ballSpeaker4);

	// FOCOS
	vector<RenderItem*> focos;
	int j = -160;
	for (int i = 0; i < 6; i++)
	{
		const physx::PxTransform* spotlightSupport = new PxTransform(j, 240, -225);
		focos.push_back(new RenderItem(CreateShape(physx::PxBoxGeometry(1, 10, 1)), spotlightSupport, Vector4(0.1, 0.1, 0.1, 1)));
		const physx::PxTransform* spotlight = new PxTransform(j, 230, -225);
		focos.push_back(new RenderItem(CreateShape(physx::PxBoxGeometry(5, 5, 5)), spotlight, Vector4(0.1, 0.1, 0.1, 1)));
		const physx::PxTransform* lightbulb = new PxTransform(j, 230, -220);
		focos.push_back(new RenderItem(CreateShape(physx::PxSphereGeometry(3)), lightbulb, Vector4(1, 1, 1, 1)));
		j += 65;
	}

	for (int i = 0; i < focos.size(); i++)
	{
		items.push_back(focos[i]); itemsToDelete.push_back(focos[i]);
	}

	// -------- ESPECTADORES --------
	gravityB = new GravityForceGenerator(Vector3(0, -10, 0));
	BuoyancyForceGenerator* bForce = new BuoyancyForceGenerator(2, 20000, 45);
	
	j = -150;
	int k = 150;
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		j = -150;
		for (int ii = 0; ii < 10; ii++)
		{
			Vector4 color = Vector4((float)(rand() % 11) / 10, (float)(rand() % 11) / 10, (float)(rand() % 11) / 10, 1);
			muelles.push_back(new Particle({ (float)k, 50.0, (float)j }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.4, 10, { 0.7, 0.5, 0.4, 1.0 }, 62500));
			const physx::PxTransform* cuerpo = new PxTransform((float)k, 25, (float)j);
			posCuerpos.push_back(Vector3((float)k, 25, (float)j));
			cuerpos.push_back(new RenderItem(CreateShape(physx::PxBoxGeometry(6, 25, 5)), cuerpo, color));
			pFReg->addRegistry(bForce, muelles[count], 4);
			pFReg->addRegistry(gravityB, muelles[count], 0);
			count++;
			j += 30;
		}
		k -= 50;
	}

	j = -150;
	k = -150;
	for (int i = 0; i < 2; i++)
	{
		j = -150;
		for (int ii = 0; ii < 10; ii++)
		{
			Vector4 color = Vector4((float)(rand() % 11) / 10, (float)(rand() % 11) / 10, (float)(rand() % 11) / 10, 1);
			muelles.push_back(new Particle({ (float)k, 50.0, (float)j }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.4, 10, { 0.7, 0.5, 0.4, 1.0 }, 62500));
			const physx::PxTransform* cuerpo = new PxTransform((float)k, 25, (float)j);
			posCuerpos.push_back(Vector3((float)k, 25, (float)j));
			cuerpos.push_back(new RenderItem(CreateShape(physx::PxBoxGeometry(6, 25, 5)), cuerpo, color));
			pFReg->addRegistry(bForce, muelles[count], 4);
			pFReg->addRegistry(gravityB, muelles[count], 0);
			count++;
			j += 30;
		}
		k += 50;
	}

	j = -30;
	k = 50;
	for (int i = 0; i < 3; i++)
	{
		j = -30;
		for (int ii = 0; ii < 6; ii++)
		{
			Vector4 color = Vector4((float)(rand() % 11) / 10, (float)(rand() % 11) / 10, (float)(rand() % 11) / 10, 1);
			muelles.push_back(new Particle({ (float)k, 50.0, float(j) }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.4, 10, { 0.7, 0.5, 0.4, 1.0 }, 62500));
			const physx::PxTransform* cuerpo = new PxTransform((float)k, 25, float(j));
			posCuerpos.push_back(Vector3((float)k, 25, (float)j));
			cuerpos.push_back(new RenderItem(CreateShape(physx::PxBoxGeometry(6, 25, 5)), cuerpo, color));
			pFReg->addRegistry(bForce, muelles[count], 4);
			pFReg->addRegistry(gravityB, muelles[count], 0);
			count++;
			j += 30;
		}
		k -= 50;
	}
	
	// -------- CIELO --------
	forceB = new Forces(3);
	wind = new WindForceGenerator(Vector3(0, 20, 0), Vector3(0, 0, 0), 250.0f);

	// ----------------------	FUEGOS ARTIFICIALES  ----------------------

	const physx::PxTransform* caja1 = new PxTransform(0, 10, 200);
	RenderItem* box1 = new RenderItem(CreateShape(physx::PxBoxGeometry(20, 20, 20)), caja1, Vector4(1, 1, 1, 1));

	fireworks = new Fireworks();
	fireworks->createFireworkRules();

	items.push_back(box1); itemsToDelete.push_back(box1);

	// -------------- SONIDO ALTAVOCES ----------------
	sonidos.push_back(new ParticleSystem(Vector3(-160, 115, -240), Vector4(1, 1, 1, 1)));
	sonidos.push_back(new ParticleSystem(Vector3(-160, 75, -240), Vector4(1, 1, 1, 1)));
	sonidos.push_back(new ParticleSystem(Vector3(160, 115, -240), Vector4(1, 1, 1, 1)));
	sonidos.push_back(new ParticleSystem(Vector3(160, 75, -240), Vector4(1, 1, 1, 1)));

	// -------------- BALAS ----------------
	vBoton = Vector3(0, 100, -398);
	const physx::PxTransform* boton = new PxTransform(vBoton);
	RenderItem* ButtonBox = new RenderItem(CreateShape(physx::PxBoxGeometry(15, 15, 3)), boton, Vector4(0.4, 0.4, 0.4, 1));
	RenderItem* Button = new RenderItem(CreateShape(physx::PxSphereGeometry(6.0)), boton, Vector4(1, 0, 0, 1));

	items.push_back(ButtonBox); itemsToDelete.push_back(ButtonBox);
	items.push_back(Button); itemsToDelete.push_back(Button);

	// Sistema de las balas que serán sólidos rígidos
	rbSystem = new RBSystem(_physics, _scene, PxTransform(0, -20, 0), this);

	// -------------- ELIMINACIÓN VECTORES ----------------

	for (int i = 0; i < platforms.size(); i++)
	{
		items.push_back(platforms[i]); itemsToDelete.push_back(platforms[i]);
	}

	for (int i = 0; i < bolas1.size(); i++)
	{
		items.push_back(bolas1[i]); itemsToDelete.push_back(bolas1[i]);
	}

	for (int i = 0; i < bolas2.size(); i++)
	{
		items.push_back(bolas2[i]); itemsToDelete.push_back(bolas2[i]);
	}

	for (int i = 0; i < cuerpos.size(); i++)
	{
		items.push_back(cuerpos[i]); itemsToDelete.push_back(cuerpos[i]);
	}
}

void Scene::deleteItems()
{
	for (RenderItem* r : itemsToDelete) {
		items.remove(r);
		DeregisterRenderItem(r);
		delete r;
	}
}

void Scene::apocalypse()
{
	if (apocalipsis)
	{
		for (int i = 0; i < platforms.size(); i++)
			platforms[i]->color = Vector4(0.4, 0.4, 0.4, 1);

		vector<Vector4> colors;
		colors.push_back(Vector4(0.25, 0, 0, 1));
		colors.push_back(Vector4(0.25, 0, 0.25, 1));
		colors.push_back(Vector4(0.12, 0, 0.25, 1));
		colors.push_back(Vector4(0, 0, 0.25, 1));
		colors.push_back(Vector4(0, 0.12, 0.25, 1));
		colors.push_back(Vector4(0, 0.25, 0.25, 1));
		colors.push_back(Vector4(0, 0.25, 0, 1));
		colors.push_back(Vector4(0.12, 0.25, 0, 1));
		colors.push_back(Vector4(0.25, 0.25, 0, 1));
		colors.push_back(Vector4(0.25, 0.12, 0, 1));

		for (int i = 0; i < bolas1.size(); i++)
			bolas1[i]->color = colors[i];
		for (int i = 0; i < bolas2.size(); i++)
			bolas2[i]->color = Vector4(0.25, 0.1, 0.17, 1);

		for (int i = 0; i < muelles.size(); i++)
			muelles[i]->setColor(Vector4(0.17, 0.3, 0.23, 1));
		for (int i = 0; i < cuerpos.size(); i++)
			cuerpos[i]->color = Vector4(0.3, 0.3, 0.3, 1);
	}
}

void Scene::buttonPressed(Vector3 rbPos)
{
	if (rbPos.x <= vBoton.x + 5 && rbPos.x >= vBoton.x - 5 && rbPos.y <= vBoton.y + 7.5 && rbPos.y >= vBoton.y - 7.5 && rbPos.z <= vBoton.z + 7.5 && rbPos.z >= vBoton.z - 7.5)
	{
		apocalipsis = true;
		apocalypse();
	}
}

void Scene::dead(Vector3 rbPos, int i)
{
	if (rbPos.x <= posCuerpos[i].x + 5 && rbPos.x >= posCuerpos[i].x - 5 && rbPos.y <= posCuerpos[i].y + 25 && rbPos.y >= posCuerpos[i].y - 25 && rbPos.z <= posCuerpos[i].z + 7.5 && rbPos.z >= posCuerpos[i].z - 7.5 && apocalipsis)
	{
		deleteBodies(i);
		blood.push_back(new ParticleSystem(posCuerpos[i], Vector4(1, 0, 0, 1)));
	}
}

void Scene::deleteBodies(int i)
{
	if (muelles[i]) {
		delete muelles[i];
		muelles[i] = nullptr;
	}
	if (cuerpos[i]) {
		DeregisterRenderItem(cuerpos[i]);
		cuerpos[i] = nullptr;
	}
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
				pFReg->addRegistry(explosion1, p, 2);
		}
	}
	if (scene == 9) 
	{
		//Se registran las fuerzas y actualiza el sistema de rb
		rbFReg->addRegistry(rbWind, rbTorque, rbSystem);
		rbSystem->update(t);
		rbFReg->updateForces(t);

		for (Particle* particle : forceY->particles) {
			if (!particle->wind)
				pFReg->addRegistry(wind, particle, 1);
		}
	}
	if (scene == 10)
	{
		rbFReg->addRegistry(rbExplosion, rbTorque, rbSystem);
		rbSystem->update(t);
	}
	if (scene == 11)
	{
		if (fuegos) fireworks->fireworksUpdate(t);

		rbSystem->update(t);

		for (int i = 0; i < sonidos.size(); i++)
			sonidos[i]->update(t, 0);

		for (int i = 0; i < blood.size(); i++)
		{
			blood[i]->update(t, 1);
		}

		for (Particle* p : forceB->particles) {
			if (!p->wind) pFReg->addRegistry(wind, p, 1);
		}
		pFReg->updateForces(t);
		rbFReg->updateForces(t);
	}
	if(scene != 5)
		pFReg->updateForces(t);
}

//M�todo que pregunta y devuelve un valor
double Scene::askK()
{
	double value;
	std::cout << "¿Que valor quiere que tenga la constante del muelle?\n";
	cin >> value;
	return value;
}
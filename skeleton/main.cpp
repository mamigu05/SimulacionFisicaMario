#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "Scene.h"

#include <iostream>



using namespace physx;
using namespace std;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
//Particle* gParticle = NULL;
//vector<Particle*>		particles;
ParticleSystem*         particles = NULL;
Fireworks*				gFirework = NULL;
Scene*                  fScene = NULL;




// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	//gParticle = new Particle(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 5.0, 3.0), Vector3(0.0, 2.0, 2.0), 0.99);
	//particles = new ParticleSystem();

	/*gFirework = new Fireworks();
	gFirework->createFireworkRules();*/
	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	fScene = new Scene();
	fScene->createFinalScene(gPhysics, gScene);
	//fScene->createScene8();
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	//gParticle->update(t);
	/*for (int i = 0; i < particles.size(); i++)
		particles[i]->update(t);*/
	//particles->update(t);
	//gFirework->fireworksUpdate(t);
	fScene->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	//delete gParticle;
	/*for (int i = 0; i < particles.size(); i++)
		delete particles[i];*/
	//delete particles;
	delete fScene; fScene = nullptr;
}

void shoot(Vector4 color, Vector3 acc, double velD, double damping, double size)
{
	Vector3 pos = GetCamera()->getEye();
	Vector3 vel = GetCamera()->getDir() * velD;
	//Vector3 acc = Vector3(0.0, -3.0, 0.0);
	//particles.push_back(new Particle(pos, vel, acc, damping, size, color));
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case '1':
	{
		fScene->exp();
		//shoot({ 1.0, 1.0, 0.0, 1.0 }, Vector3(0.0, -3.0, 0.0), 50, 0.99, 1.0);
		break;
	}
	case '2':
	{
		fScene->addRB(PxTransform(GetCamera()->getTransform().p), GetCamera()->getDir() * 250);
		//shoot({ 0.1, 0.1, 0.1, 1.0 }, Vector3(0.0, -6.0, 0.0), 35, 0.99, 4.0);
		break;
	}
	case '3':
	{
		//shoot({ 1.0, 0.5, 0.0, 1.0 }, Vector3(0.0, 0.1, 0.0), 5, 0.99, 1.0);
		break;
	}
	case '4':
	{
		//gFirework->createFirework();
		break;
	}
	case '5':
	{
		if(fScene->getScene() == 5)
			fScene->pFReg->updateForces(1);
		if (fScene->getScene() == 10)
			fScene->rbFReg->updateForces(1);
		break;
	}
	case '6':
	{
		//Llama al m�todo para sumarle valor a la constante el�stica
		fScene->addK();
		break;
	}
	case '7':
	{
		//Llama al m�todo para restarle valor a la constante el�stica
		fScene->subK();
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}
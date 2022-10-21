#pragma once

#include "RenderUtils.hpp"
#include <list>

using namespace std;

class Particle
{
private:
	RenderItem* renderItem;

	Vector3 v;
	Vector3 a;

	double damping;
	
	double _remaining_time, death;
public:
	physx::PxTransform pose;
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, double damping, double size, Vector4 color, double time);
	~Particle();

	void update(double t);
	//virtual Particle* clone() const;
};

class Firework : public Particle
{
public:
	double age;
	Firework() : Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.99, 1.0, { 1.0, 1.0, 0.0, 1.0 }, 25) {};
	bool update(double t);
};

class ParticleSystem
{
protected:
	Vector3 v;
	list<Particle*> _particles;
	list<Particle*> _particlesToDelete;
	//std::list<ParticleGenerator*> _particleGenerators;
public:
	ParticleSystem();
	void update(double t);
	//ParticleGenerator* getParticleGenerator(string name);
	void generateFireworkSystem();
};


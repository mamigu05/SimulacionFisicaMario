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
	virtual Particle* clone() const;
};

class ParticleSystem
{
protected:
	Vector3 v;
	list<Particle*> _particles;
	list<Particle*> _particlesToDelete;
	//std::list<ParticleGenerator*> _particleGenerators;
	Vector3 _gravity;
public:
	ParticleSystem();
	void update(double t);
	//ParticleGenerator* getParticleGenerator(string name);
	void generateFireworkSystem();
};


#pragma once

#include "RenderUtils.hpp"
#include <list>

class Particle
{
private:
	physx::PxTransform pose;
	RenderItem* renderItem;

	Vector3 v;
	Vector3 a;

	double damping;
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, double damping, double size, Vector4 color);
	~Particle();

	void update(double t);
	virtual Particle* clone() const;
};

class ParticleSystem
{
protected:
	std::list<Particle*> _particles;
	//std::list<ParticleGenerator*> _particleGenerators;
	Vector3 _gravity;
public:
	void update(double t);
	//ParticleGenerator* getParticleGenerator(string name);
	void generateFireworkSystem();
};


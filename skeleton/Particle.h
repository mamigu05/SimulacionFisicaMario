#pragma once

#include "RenderUtils.hpp"
#include <list>

using namespace std;

class Particle
{
private:
	//RenderItem de la part�cula
	RenderItem* renderItem;
	//Vector de colores de la part�cula
	Vector4 color;
	//Vector de aceleraci�n de la part�cula
	Vector3 a;
	//Indice de la fuerza de refracci�n
	double damping;
	//Tiempo, muerte, �ndice inverso de la masa y tama�o de la part�cula
	double remaining_time;
	double death, inverse_mass, size;
public:
	//Vector de la posici�n de la part�cula
	physx::PxTransform pose;
	//Vector de la velocidad de la part�cula
	Vector3 v;
	//Constructora de la clase Particle
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, double damping, double _size, Vector4 _color, double inverse);
	//Destructora de la clase Particle
	~Particle();
	//M�todo que actualiza los vectores de la part�cula
	void update(double t);
	//M�todo que asigna un color a la part�cula
	void setColor(Vector4 _color);
};

const enum tipos { FIREWORK, SMOKE, EXPLOSION, FW_UNKNOWN_TYPE };

class Firework : public Particle
{
public:
	//Vida de la part�cula
	double age;
	//Tipo de la part�cula
	unsigned type;
	//Constructora de la clase Firework
	Firework() : Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.99, 1.0, Vector4(1.0, 1.0, 0.0, 1.0), 9.99) {};
	//M�todo que actualiza la vida y decide si muere o no
	bool update(double t);
	//M�todo que comprueba si la part�cula est� activa
	bool isActive() const { return type != FW_UNKNOWN_TYPE; };
	//M�todo que desactiva la part�cula
	void setInactive() { type = FW_UNKNOWN_TYPE; };
};

class Fireworks
{
	//Struct que guarda la carga de Firework
	struct Payload
	{
		unsigned type, count;
		Payload(unsigned _type, unsigned _count)
		{
			type = _type; count = _count;
		}
		void set(unsigned _type, unsigned _count)
		{
			type = _type; count = _count;
		}
	};

	//Struct que configura las reglas de Firework
	struct FireworkRule
	{
		//Tipo de la part�cula de Firework
		unsigned type;
		//Rango de vida de la part�cula
		int minAge, maxAge;
		//Velocidad de la part�cula
		int minVelocity, maxVelocity;
		//Damping de la part�cula
		double damping;
		//Vector de payloads
		vector<Payload> payloads;

		//M�todo que atribuye valores a una regla
		void setParameters(unsigned _type, int _min, int _max, int _minVel, int _maxVel, double _damping, Payload _payload)
		{
			type = _type;
			minAge = _min;
			maxAge = _max;
			minVelocity = _minVel;
			maxVelocity = _maxVel;
			damping = _damping;
			payloads.push_back(_payload);
		}

		//M�todo que atribuye valores a un nuevo Firework
		void create(Firework* firework, Payload payload, const Firework* parent = nullptr) const
		{
			firework->type = type;

			int max = maxAge * 100;
			int min = minAge * 100;
			max = max - min + 1;

			double age = rand() % max + min;
			firework->age = age / 100;
			double t = 1.0;
			if (type == 0)
				t = 1;
			else if (type == 2)
				t = 0;
			Vector4 color = Vector4((float)(rand() % 11) / 10, (float)(rand() % 11) / 10, (float)(rand() % 11) / 10, t);
			firework->setColor(color);
			Vector3 v;
			if (parent != NULL)
			{
				firework->pose = parent->pose;
				if(type == 0)
					v = Vector3((rand() % maxVelocity - minVelocity) / 10, -2, (rand() % maxVelocity - minVelocity) / 10);
				else if(type == 2)
					v = Vector3((rand() % maxVelocity - minVelocity), (rand() % 10 - 5), (rand() % maxVelocity - minVelocity));
			}
			else
			{
				firework->pose = physx::PxTransform(10.0f, 10.0f, 10.0f);
				v = Vector3((rand() % (maxVelocity / 2) - (minVelocity / 2)) / 10, 15, (rand() % (maxVelocity / 2) - (minVelocity / 2)) / 10);
			}
			firework->v = v;
		}
	};

private:
	//Vector que guarda las reglas de las part�culas
	vector<FireworkRule*> rules;
	//Vector que guarda los fireworks creados
	vector<Firework*> fireworks;

public:
	//M�todo que inicializa las reglas y dispara un firework
	void createFireworkRules();
	//M�todo que elimina los punteros a firework
	void deleteFireworks();
	//M�todo que crea un puntero a un firework nuevo vac�o
	Firework* allocNewFirework();
	//M�todo que crea un firework
	void fireworksCreate(Payload p, const Firework* parent = nullptr);
	//M�todo que devuelva la regla de un tipo
	FireworkRule* getRuleFromType(int type) { return rules[type]; };
	//M�todo que actualiza los fuegos artificiales
	void fireworksUpdate(double t);
	//M�todo que dispara un nuevo firework
	void createFirework() { fireworksCreate(Payload(1, 1)); };
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


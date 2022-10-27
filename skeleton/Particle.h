#pragma once

#include "RenderUtils.hpp"
#include <list>

using namespace std;

class Particle
{
private:
	//RenderItem de la partícula
	RenderItem* renderItem;
	//Vector de colores de la partícula
	Vector4 color;
	//Vector de aceleración de la partícula
	Vector3 a;
	//Indice de la fuerza de refracción
	double damping;
	//Tiempo, muerte, índice inverso de la masa y tamaño de la partícula
	double remaining_time;
	double death, inverse_mass, size;
public:
	//Vector de la posición de la partícula
	physx::PxTransform pose;
	//Vector de la velocidad de la partícula
	Vector3 v;
	//Constructora de la clase Particle
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, double damping, double _size, Vector4 _color, double inverse);
	//Destructora de la clase Particle
	~Particle();
	//Método que actualiza los vectores de la partícula
	void update(double t);
	//Método que asigna un color a la partícula
	void setColor(Vector4 _color);
};

const enum tipos { FIREWORK, SMOKE, EXPLOSION, FW_UNKNOWN_TYPE };

class Firework : public Particle
{
public:
	//Vida de la partícula
	double age;
	//Tipo de la partícula
	unsigned type;
	//Constructora de la clase Firework
	Firework() : Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.99, 1.0, Vector4(1.0, 1.0, 0.0, 1.0), 9.99) {};
	//Método que actualiza la vida y decide si muere o no
	bool update(double t);
	//Método que comprueba si la partícula está activa
	bool isActive() const { return type != FW_UNKNOWN_TYPE; };
	//Método que desactiva la partícula
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
		//Tipo de la partícula de Firework
		unsigned type;
		//Rango de vida de la partícula
		int minAge, maxAge;
		//Velocidad de la partícula
		int minVelocity, maxVelocity;
		//Damping de la partícula
		double damping;
		//Vector de payloads
		vector<Payload> payloads;

		//Método que atribuye valores a una regla
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

		//Método que atribuye valores a un nuevo Firework
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
	//Vector que guarda las reglas de las partículas
	vector<FireworkRule*> rules;
	//Vector que guarda los fireworks creados
	vector<Firework*> fireworks;

public:
	//Método que inicializa las reglas y dispara un firework
	void createFireworkRules();
	//Método que elimina los punteros a firework
	void deleteFireworks();
	//Método que crea un puntero a un firework nuevo vacío
	Firework* allocNewFirework();
	//Método que crea un firework
	void fireworksCreate(Payload p, const Firework* parent = nullptr);
	//Método que devuelva la regla de un tipo
	FireworkRule* getRuleFromType(int type) { return rules[type]; };
	//Método que actualiza los fuegos artificiales
	void fireworksUpdate(double t);
	//Método que dispara un nuevo firework
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


#ifndef _ParticleSystem
#define _ParticleSystem

#include <list>
#include "AzulCore.h"

class Emitter;
class ParticleSystemTimer;
class ParticleEffect;
class ParticleSystem
{
	friend class ParticleSystemAttorney;
public:
	struct EffectData
	{
		ParticleEffect* effect;
		float StartDelay;

		bool operator<(const EffectData& b) { return this->StartDelay < b.StartDelay; };
	};

private:
	std::list<EffectData> effects;
	std::list<Emitter*> emitters;
	using EffectIt = std::list<Emitter*>::iterator;
	using DataIt = std::list<EffectData>::iterator;
	DataIt it;
	ParticleSystemTimer* timer;

	Matrix rot;
	Vect pos;

	void StartNext();

public:
	ParticleSystem();
	ParticleSystem(Matrix rotation, Vect position);
	ParticleSystem(const ParticleSystem&) = delete;
	ParticleSystem& operator=(const ParticleSystem&) = delete;
	~ParticleSystem();

	void Set(Matrix rotation, Vect position);
	void SetAll(Matrix rotation, Vect position);

	void Add(ParticleEffect* e, float delay);
	void Add(EffectData e);

	void Start();

	Emitter* ForceStart(int index);
	Emitter* ForceStart(ParticleEffect* effect);
	void ForceStartAll();

	void StopAll();

	std::list<Emitter*> GetActiveEmitters();
};

#endif _ParticleSystem
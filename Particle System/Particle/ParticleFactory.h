#ifndef _ParticleFactory
#define _ParticleFactory

#include "ParticlePool.h"

class ParticleFactory
{
private:
	static ParticleFactory* ptrInstance;

	ParticleFactory() = default;
	ParticleFactory(const ParticleFactory&) = delete;
	ParticleFactory& operator=(const ParticleFactory&) = delete;
	~ParticleFactory() = default;

	static ParticleFactory& Instance()
	{
		if (!ptrInstance) ptrInstance = new ParticleFactory();
		return *ptrInstance;
	}

	ParticlePool pool;

	Particle* privCreateParticle();
	void privRecycleParticle(Particle* p);

public:
	static Particle* createParticle() { return Instance().privCreateParticle(); };
	static void recycleParticle(Particle* p) { Instance().privRecycleParticle(p); };
	static void Terminate();
};

#endif _ParticleFactory
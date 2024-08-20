#include "ParticleFactory.h"

ParticleFactory* ParticleFactory::ptrInstance = nullptr;

Particle* ParticleFactory::privCreateParticle()
{
	Particle* p = pool.getParticle();
	return p;
}

void ParticleFactory::privRecycleParticle(Particle* p)
{
	pool.returnParticle(p);
}

void ParticleFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
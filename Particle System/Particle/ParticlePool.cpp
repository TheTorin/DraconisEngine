#include "Particle.h"
#include "ParticlePool.h"

Particle* ParticlePool::getParticle()
{
	Particle* p;

	if (recycledParticles.empty())
	{
		p = new Particle();
	}
	else
	{
		p = recycledParticles.top();
		recycledParticles.pop();
	}
	activeParticles.push_back(p);
	return p;
}

void ParticlePool::returnParticle(Particle* p)
{
	recycledParticles.push(p);
	activeParticles.remove(p);
}

ParticlePool::~ParticlePool()
{
	while (!recycledParticles.empty())
	{
		delete recycledParticles.top();
		recycledParticles.pop();
	}
	while (!activeParticles.empty())
	{
		delete activeParticles.front();
		activeParticles.pop_front();
	}
}
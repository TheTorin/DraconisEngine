#ifndef _ParticlePool
#define _ParticlePool

#include <stack>
#include <list>

class Particle;
class ParticlePool
{
private:
	std::stack<Particle*> recycledParticles;
	std::list<Particle*> activeParticles;

public:
	ParticlePool() = default;
	ParticlePool(const ParticlePool&) = delete;
	ParticlePool& operator=(const ParticlePool&) = delete;
	~ParticlePool();

	Particle* getParticle();
	void returnParticle(Particle* p);
};

#endif _ParticlePool
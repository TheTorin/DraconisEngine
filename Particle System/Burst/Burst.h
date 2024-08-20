#ifndef _Burst
#define _Burst

#include "AzulCore.h"

class ParticleEffect;
class Particle;
class Burst
{
private:
	ParticleEffect* effect;
	Particle** particles;
	float currentScale;
	int particlesLen;

	float timeLeft;

public:
	Burst() = default;
	Burst(ParticleEffect* parent, int numParticles, Vect spawnPos, Vect upDir, Vect forwardDir, float startScale, float lifetime);
	Burst(const Burst&) = delete;
	Burst& operator=(const Burst&) = delete;
	~Burst();

	void Set(ParticleEffect* parent, int numParticles, Vect spawnPos, Vect upDir, Vect forwardDir, float startScale, float lifetime);

	void Draw();

	float GetTimeLeft();
};

#endif _Burst
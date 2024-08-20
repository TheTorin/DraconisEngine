#ifndef _ParticleEffect
#define _ParticleEffect

#include <vector>
#include "AzulCore.h"

class Emitter;
class AnimatedSprite;
class ParticleEffect
{
	friend class ParticleEffectAttorney;
private:
	std::vector<Emitter*> activeEmitters;
	//AnimatedSprite* particleSprite;
	GraphicsObject_TextureFlat* particleSprite;

	void RemoveEmitter(Emitter* toRemove);
public:
	Vect gravity;

	float scaleStart = 1;
	float scaleChange = 0;

	float emitterLife = -1;
	float particleLife = 5;
	float minBurstFrequency = 0.3f;
	float maxBurstFrequency = 0.5f;

	int minParticlesPerBurst = 50;
	int maxParticlesPerBurst = 100;

	float minSpriteAngle = 0;
	float maxSpriteAngle = 0;
	float minSpriteRotation = 0;
	float maxSpriteRotation = 0;

	float maxBursts = -1;
	float minEmitAngle = 0;
	float maxEmitAngle = MATH_PI;

	float minSpeed = 1;
	float maxSpeed = 5;

	ParticleEffect() = default;
	ParticleEffect(GraphicsObject_TextureFlat* sprite, Vect gravity);
	ParticleEffect(const ParticleEffect&) = delete;
	ParticleEffect& operator=(const ParticleEffect&) = delete;
	~ParticleEffect();

	Emitter* SpawnEmitter(Matrix rotation, Vect Pos, Vect Vel);
};

#endif _ParticleEffect
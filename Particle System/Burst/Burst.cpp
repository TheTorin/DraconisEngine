#include "Particle.h"
#include "Burst.h"
#include "ParticleEffectAttorney.h"
#include "ParticleFactory.h"
#include "TimeManager.h"
#include "AnimatedSprite.h"
#include "DraconisSprite.h"
#include "SceneManager.h"

Burst::Burst(ParticleEffect* parent, int numParticles, Vect spawnPos, Vect upDir, Vect forwardDir, float startScale, float lifeTime)
	:effect(parent), currentScale(startScale), timeLeft(lifeTime)
{
	particles = new Particle*[numParticles];

	float emitRange = parent->maxEmitAngle - parent->minEmitAngle;
	float speedRange = parent->maxSpeed - parent->minSpeed;

	for (int i = 0; i < numParticles; i++)
	{
		particles[i] = ParticleFactory::createParticle();
		
		//First, set the initial velocity. Rotate upDir by random angle, and then rotate around upDir for a 'cone' shape of possible velocities
		float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / emitRange) + parent->minEmitAngle;
		Vect particleVel = upDir * Matrix(RotAxisAngleType::ROT_AXIS_ANGLE, forwardDir, angle);
		angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (2 * MATH_PI));
		particleVel *= Matrix(RotAxisAngleType::ROT_AXIS_ANGLE, upDir, angle);

		float speed = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / speedRange) + parent->minSpeed;
		particleVel = particleVel.getNorm() * speed;

		float startAngleRange = parent->maxSpriteAngle - parent->minSpriteAngle;
		angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / startAngleRange) + parent->minSpriteAngle;

		float rotationRange = parent->maxSpriteRotation - parent->minSpriteRotation;
		float rotation = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / rotationRange) + parent->minSpriteRotation;

		particles[i]->Set(spawnPos, particleVel, parent->gravity, angle, rotation);
	}

	particlesLen = numParticles;
}

void Burst::Set(ParticleEffect* parent, int numParticles, Vect spawnPos, Vect upDir, Vect forwardDir, float startScale, float lifeTime)
{
	effect = parent;
	currentScale = startScale;
	timeLeft = lifeTime;

	particles = new Particle*[numParticles];

	float emitRange = parent->maxEmitAngle - parent->minEmitAngle;
	float speedRange = parent->maxSpeed - parent->minSpeed;

	for (int i = 0; i < numParticles; i++)
	{
		particles[i] = ParticleFactory::createParticle();

		//First, set the initial velocity. Rotate upDir by random angle, and then rotate around upDir for a 'cone' shape of possible velocities
		float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / emitRange) + parent->minEmitAngle;
		Vect particleVel = upDir * Matrix(RotAxisAngleType::ROT_AXIS_ANGLE, forwardDir, angle);
		angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (2 * MATH_PI));
		particleVel *= Matrix(RotAxisAngleType::ROT_AXIS_ANGLE, upDir, angle);

		float speed = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / speedRange) + parent->minSpeed;
		particleVel = particleVel.getNorm() * speed;

		float startAngleRange = parent->maxSpriteAngle - parent->minSpriteAngle;
		angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / startAngleRange) + parent->minSpriteAngle;

		float rotationRange = parent->maxSpriteRotation - parent->minSpriteRotation;
		float rotation = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / rotationRange) + parent->minSpriteRotation;

		particles[i]->Set(spawnPos, particleVel, parent->gravity, angle, rotation);
	}

	particlesLen = numParticles;
}

void Burst::Draw()
{
	timeLeft -= TimeManager::getFrameTime();

	//DraconisSprite* img = ParticleEffectAttorney::SpriteAccess::GetSprite(effect)->GetFrame(frameIndex);
	GraphicsObject_TextureFlat* img = ParticleEffectAttorney::SpriteAccess::GetSprite(effect);

	Vect camPos;
	Vect rightTest;
	SceneManager::getCurrentScene()->getCurrentCamera()->getRight(rightTest);
	SceneManager::getCurrentScene()->getCurrentCamera()->getPos(camPos);

	Matrix scale = Matrix(SCALE, currentScale, currentScale, currentScale);

	for (int i = 0; i < particlesLen; ++i)
	{
		Vect pos = particles[i]->GetPos();
		Vect toCam = camPos - pos;
		toCam.norm();
		toCam.set(toCam.X(), toCam.Y(), toCam.Z(), 0);
		Vect toCross = toCam + rightTest;
		Vect up = toCam.cross(toCross);
		up.set(up.X(), up.Y(), up.Z(), 0);
		//Vect up = Vect(0, 1, 0, 0);
		Vect side = toCam.cross(up);
		side.set(side.X(), side.Y(), side.Z(), 0);

		Matrix rot = Matrix(side, up, toCam, Vect(0, 0, 0, 1));
		rot = Matrix(ROT_Z, particles[i]->GetAngle()) * rot;

		Matrix world = rot * scale * Matrix(TRANS, pos);
		img->SetWorld(world);

		img->Render(SceneManager::getCurrentScene()->getCurrentCamera());
	}

	currentScale += (effect->scaleChange * TimeManager::getFrameTime());
}

float Burst::GetTimeLeft()
{
	return timeLeft;
}

Burst::~Burst()
{
	for (int i = 0; i < particlesLen; ++i)
	{
		ParticleFactory::recycleParticle(particles[i]);
	}
	delete[] particles;
}
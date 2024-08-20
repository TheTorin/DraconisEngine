#include "Emitter.h"
#include "EmitterFactory.h"
#include "Burst.h"
#include "ParticleEffect.h"
#include "ParticleEffectAttorney.h"
#include "BurstFactory.h"
#include "TimeManager.h"

Emitter::Emitter()
{
	parent = nullptr;
	maxBursts = 0;
	minBurstFrequency = 0;
	maxBurstFrequency = 0;
	alive = false;
	rotation = Matrix(IDENTITY);
	position = Vect();
	velocity = Vect();
}

Emitter::Emitter(ParticleEffect* pe, Matrix rot, Vect pos, Vect vel)
	:parent(pe), rotation(rot), position(pos), velocity(vel)
{
	maxBursts = parent->maxBursts;
	minBurstFrequency = parent->minBurstFrequency;
	maxBurstFrequency = parent->maxBurstFrequency;
	alive = true;
	if (parent->emitterLife > 0) SubmitAlarmRegistration(AlarmableManager::ALARM_0, parent->emitterLife);
	frequencyRange = maxBurstFrequency - minBurstFrequency;
	float time = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / frequencyRange) + minBurstFrequency;
	SubmitAlarmRegistration(AlarmableManager::ALARM_1, time);
}

void Emitter::Set(ParticleEffect* pe, Matrix rot, Vect pos, Vect vel)
{
	parent = pe;
	rotation = rot;
	position = pos;
	velocity = vel;

	maxBursts = parent->maxBursts;
	minBurstFrequency = parent->minBurstFrequency;
	maxBurstFrequency = parent->maxBurstFrequency;
	alive = true;
	if (parent->emitterLife > 0) SubmitAlarmRegistration(AlarmableManager::ALARM_0, parent->emitterLife);
	frequencyRange = maxBurstFrequency - minBurstFrequency;
	float time = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / frequencyRange) + minBurstFrequency;
	SubmitAlarmRegistration(AlarmableManager::ALARM_1, time);
}

void Emitter::Register()
{
	SubmitDrawRegistration();
}

void Emitter::Draw2D()
{
	listIt it;
	float timePassed = TimeManager::getFrameTime();
	position += velocity * timePassed;

	//First, cull all bursts that are out of time so that we don't have to do fancy iterator shenanigans later
	while (!activeBursts.empty() && activeBursts.front()->GetTimeLeft() <= timePassed)
	{
		BurstFactory::recycleBurst(activeBursts.front());
		activeBursts.pop_front();
	}

	if (activeBursts.empty() && !alive)
	{
		SubmitDrawDeregistration();
		SubmitAlarmDeregistration(AlarmableManager::ALARM_1);
		EmitterFactory::recycleEmitter(this);
		ParticleEffectAttorney::EmitterManagement::RemoveEmitter(parent, this);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	for (it = activeBursts.begin(); it != activeBursts.end(); ++it)
	{
		(*it)->Draw();
	}

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

void Emitter::Alarm0()
{
	alive = false;
}

void Emitter::Alarm1()
{
	if (alive)
	{
		if (activeBursts.size() < parent->maxBursts || parent->maxBursts < 0)
		{
			SpawnBurst();
		}
		float time = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / frequencyRange) + minBurstFrequency;
		SubmitAlarmRegistration(AlarmableManager::ALARM_1, time);
	}
}

void Emitter::SpawnBurst()
{
	Vect emitUp = rotation.get(MatrixRowType::ROW_1);
	Vect emitForward = rotation.get(MatrixRowType::ROW_2);
	int diff = parent->maxParticlesPerBurst - parent->minParticlesPerBurst;
	int burstParticles = (rand() % diff) + parent->minParticlesPerBurst;
	Burst* b = BurstFactory::createBurst();
	b->Set(parent, burstParticles, position, emitUp, emitForward, parent->scaleStart, parent->particleLife);
	activeBursts.push_back(b);
}

void Emitter::StopSpawning()
{
	alive = false;
}

void Emitter::SetPosition(Vect newPos)
{
	position = newPos;
}

void Emitter::SetVelocity(Vect newVel)
{
	velocity = newVel;
}

void Emitter::SetRotation(Matrix newRot)
{
	rotation = newRot;
}

void Emitter::ChangeInfo(Vect addVel, Vect addPos, Matrix multRot)
{
	position += addPos;
	velocity += addVel;
	rotation *= multRot;
}

void Emitter::Set(Matrix rot, Vect pos, Vect vel)
{
	rotation = rot;
	position = pos;
	velocity = vel;
}

Emitter::~Emitter()
{

}
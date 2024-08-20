#include "ParticleSystemTimer.h"
#include "ParticleSystemAttorney.h"
#include "TimeManager.h"

ParticleSystemTimer::ParticleSystemTimer(ParticleSystem* parent)
{
	p = parent;
}

void ParticleSystemTimer::Begin()
{
	SubmitUpdateRegistration();
}

void ParticleSystemTimer::SetTimer(float t)
{
	currTime = 0;
	time = t;
}

void ParticleSystemTimer::Update()
{
	currTime += TimeManager::getFrameTime();
	if (currTime >= time)
	{
		ParticleSystemAttorney::StartNext(p);
	}
}

void ParticleSystemTimer::Finish()
{
	SubmitUpdateDeregistration();
}
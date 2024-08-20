#include "ParticleSystem.h"
#include "ParticleSystemTimer.h"
#include "ParticleEffect.h"
#include "Emitter.h"

ParticleSystem::ParticleSystem()
{
	timer = new ParticleSystemTimer(this);
	rot = Matrix(IDENTITY);
	pos = Vect();
}

ParticleSystem::ParticleSystem(Matrix rotation, Vect position)
{
	timer = new ParticleSystemTimer(this);
	rot = rotation;
	pos = position;
}

void ParticleSystem::Set(Matrix rotation, Vect position)
{
	rot = rotation;
	pos = position;
}

void ParticleSystem::SetAll(Matrix rotation, Vect position)
{
	rot = rotation;
	pos = position;

	for (EffectIt it1 = emitters.begin(); it1 != emitters.end(); it1)
	{
		Emitter* e = *it1;
		if (e->alive)
		{
			e->SetRotation(rotation);
			e->SetPosition(position);
		}
		else
		{
			EffectIt kill = it1;
			++it1;
			emitters.erase(kill);
		}
	}
}

void ParticleSystem::Add(ParticleEffect* p, float delay)
{
	EffectData e;
	e.effect = p;
	e.StartDelay = delay;
	effects.push_back(e);
}

void ParticleSystem::Add(EffectData e)
{
	effects.push_back(e);
}

std::list<Emitter*> ParticleSystem::GetActiveEmitters()
{
	return emitters;
}

void ParticleSystem::Start()
{
	effects.sort();
	it = effects.begin();
	while ((*it).StartDelay == 0.0f && it != effects.end())
	{
		Emitter* e = (*it).effect->SpawnEmitter(rot, pos, Vect());
		emitters.push_back(e);
		++it;
	}
	timer->Begin();
	timer->SetTimer((*it).StartDelay);
}

void ParticleSystem::StartNext()
{
	float currDelay = (*it).StartDelay;
	while (it != effects.end() && (*it).StartDelay == currDelay)
	{
		Emitter* e = (*it).effect->SpawnEmitter(rot, pos, Vect());
		emitters.push_back(e);
		++it;
	}
	if (it != effects.end()) timer->SetTimer((*it).StartDelay);
	else timer->Finish();
}

Emitter* ParticleSystem::ForceStart(int index)
{
	DataIt start = effects.begin();
	for (int i = 0; i < index; ++i)
	{
		++start;
	}
	Emitter* e = (*start).effect->SpawnEmitter(rot, pos, Vect());
	emitters.push_back(e);
	return e;
}

Emitter* ParticleSystem::ForceStart(ParticleEffect* p)
{
	for (DataIt start = effects.begin(); start != effects.end(); ++start)
	{
		if ((*start).effect == p)
		{
			Emitter* e = (*start).effect->SpawnEmitter(rot, pos, Vect());
			emitters.push_back(e);
			return e;
		}
	}
	return NULL;
}

void ParticleSystem::ForceStartAll()
{
	for (DataIt start = effects.begin(); start != effects.end(); ++start)
	{
		Emitter* e = (*start).effect->SpawnEmitter(rot, pos, Vect());
		emitters.push_back(e);
	}
}

void ParticleSystem::StopAll()
{
	for (EffectIt stop = emitters.begin(); stop != emitters.end(); ++stop)
	{
		(*stop)->StopSpawning();
	}
}

ParticleSystem::~ParticleSystem()
{
	delete timer;
}
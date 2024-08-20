#ifndef _ParticleEffectManagerAttorney
#define _ParticleEffectManagerAttorney

#include "ParticleEffectManager.h"

class ParticleEffectManagerAttorney
{
	friend class Draconis;
private:
	static void Terminate() { ParticleEffectManager::Terminate(); };
};

#endif _ParticleEffectManagerAttorney
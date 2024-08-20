#ifndef _ParticleSystemAttorney
#define _ParticleSystemAttorney

#include "ParticleSystem.h"

class ParticleSystemAttorney
{
	friend class ParticleSystemTimer;
private:
	static void StartNext(ParticleSystem* p) { p->StartNext(); };
};

#endif _ParticleSystemAttorney
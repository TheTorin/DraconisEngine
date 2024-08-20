#ifndef _ParticleEffectAttorney
#define _ParticleEffectAttorney

#include "ParticleEffect.h"

class ParticleEffectAttorney
{
public:
	class SpriteAccess
	{
		friend class Burst;
	private:
		static GraphicsObject_TextureFlat* GetSprite(ParticleEffect* p) { return p->particleSprite; };
	};
	class EmitterManagement
	{
		friend class Emitter;
	private:
		static void RemoveEmitter(ParticleEffect* p, Emitter* e) { p->RemoveEmitter(e); };
	};
};

#endif _ParticleEffectAttorney
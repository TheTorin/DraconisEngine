#include "ParticleEffect.h"
#include "EmitterFactory.h"
#include "Emitter.h"

ParticleEffect::ParticleEffect(GraphicsObject_TextureFlat* sprite, Vect grav)
{
	particleSprite = sprite;
	gravity = grav;
}

Emitter* ParticleEffect::SpawnEmitter(Matrix rot, Vect pos, Vect vel)
{
	Emitter* e = EmitterFactory::createEmitter();
	e->Set(this, rot, pos, vel);
	activeEmitters.push_back(e);
	return e;
}

void ParticleEffect::RemoveEmitter(Emitter* e)
{
	std::vector<Emitter*>::iterator it;
	for (it = activeEmitters.begin(); it != activeEmitters.end(); ++it)
	{
		if (*it == e)
		{
			activeEmitters.erase(it);
			return;
		}
	}
}

ParticleEffect::~ParticleEffect()
{
	delete particleSprite;
}
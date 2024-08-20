#include "ParticleEffectManager.h"
#include "ParticleEffect.h"
#include "EmitterFactory.h"
#include "BurstFactory.h"
#include "ParticleFactory.h"

ParticleEffectManager* ParticleEffectManager::ptrInstance = nullptr;

int ParticleEffectManager::privLoad(std::string key, GraphicsObject_TextureFlat* sprite, Vect gravity)
{
	ParticleMap::iterator it = LoadedEffects.find(key);
	if (it != LoadedEffects.end())
	{
		throw std::invalid_argument("Error while loading Particle Effect: Key " + key + " is already used!");
		return EXIT_FAILURE;
	}
	ParticleEffect* p = new ParticleEffect(sprite, gravity);
	LoadedEffects.insert({ key, p });
	return EXIT_SUCCESS;
}

ParticleEffect* ParticleEffectManager::privGet(const std::string key)
{
	ParticleMap::iterator it = LoadedEffects.find(key);
	if (it == LoadedEffects.end())
	{
		throw std::invalid_argument("Error while retrieving Particle Effect: Key " + key + " not found!");
		return NULL;
	}
	return it->second;
}

void ParticleEffectManager::Terminate()
{
	for (ParticleMap::iterator it = Instance().LoadedEffects.begin(); it != Instance().LoadedEffects.end(); ++it)
	{
		delete it->second;
	}

	EmitterFactory::Terminate();
	BurstFactory::Terminate();
	ParticleFactory::Terminate();

	delete ptrInstance;
	ptrInstance = nullptr;
}
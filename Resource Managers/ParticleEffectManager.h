#ifndef _ParticleEffectManager
#define _ParticleEffectManager

#include <map>
#include <string>
#include "AzulCore.h"

class ParticleEffect;
class ParticleEffectManager
{
	friend class ParticleEffectManagerAttorney;
private:
	static ParticleEffectManager* ptrInstance;

	ParticleEffectManager() = default;
	ParticleEffectManager(const ParticleEffectManager&) = delete;
	ParticleEffectManager& operator=(const ParticleEffectManager&) = delete;
	~ParticleEffectManager() = default;

	static ParticleEffectManager& Instance()
	{
		if (!ptrInstance) ptrInstance = new ParticleEffectManager();
		return *ptrInstance;
	}

	using ParticleMap = std::map<std::string, ParticleEffect*>;
	ParticleMap LoadedEffects;

	int privLoad(std::string key, GraphicsObject_TextureFlat* sprite, Vect gravity);
	ParticleEffect* privGet(const std::string key);

	static void Terminate();

public:
	static int Load(std::string key, GraphicsObject_TextureFlat* sprite, Vect gravity) { return Instance().privLoad(key, sprite, gravity); };
	static ParticleEffect* Get(const std::string key) { return Instance().privGet(key); };
};

#endif _ParticleEffectManager
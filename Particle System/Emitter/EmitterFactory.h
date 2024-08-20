#ifndef _EmitterFactory
#define _EmitterFactory

#include "EmitterPool.h"

class EmitterFactory
{
private:
	static EmitterFactory* ptrInstance;

	EmitterFactory() = default;
	EmitterFactory(const EmitterFactory&) = delete;
	EmitterFactory& operator=(const EmitterFactory&) = delete;
	~EmitterFactory() = default;

	static EmitterFactory& Instance()
	{
		if (!ptrInstance) ptrInstance = new EmitterFactory();
		return *ptrInstance;
	}

	EmitterPool pool;

	Emitter* privCreateEmitter();
	void privRecycleEmitter(Emitter* e);

public:
	static Emitter* createEmitter() { return Instance().privCreateEmitter(); };
	static void recycleEmitter(Emitter* e) { return Instance().privRecycleEmitter(e); };
	static void Terminate();
};

#endif _EmitterFactory
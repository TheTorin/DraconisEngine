#include "EmitterFactory.h"
#include "Emitter.h"

EmitterFactory* EmitterFactory::ptrInstance = nullptr;

Emitter* EmitterFactory::privCreateEmitter()
{
	Emitter* e = pool.getEmitter();
	e->Register();
	return e;
}

void EmitterFactory::privRecycleEmitter(Emitter* e)
{
	pool.returnEmitter(e);
}

void EmitterFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
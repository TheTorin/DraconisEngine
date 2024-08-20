#include "EmitterPool.h"
#include "Emitter.h"

Emitter* EmitterPool::getEmitter()
{
	Emitter* e;

	if (recycledEmitters.empty())
	{
		e = new Emitter();
	}
	else
	{
		e = recycledEmitters.top();
		recycledEmitters.pop();
	}
	activeEmitters.push_back(e);
	return e;
}

void EmitterPool::returnEmitter(Emitter* e)
{
	recycledEmitters.push(e);
	activeEmitters.remove(e);
}

EmitterPool::~EmitterPool()
{
	while (!recycledEmitters.empty())
	{
		delete recycledEmitters.top();
		recycledEmitters.pop();
	}
	while (!activeEmitters.empty())
	{
		delete activeEmitters.front();
		activeEmitters.pop_front();
	}
}
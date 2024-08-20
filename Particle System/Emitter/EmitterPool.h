#ifndef _EmitterPool
#define _EmitterPool

#include <stack>
#include <list>

class Emitter;
class EmitterPool
{
private:
	std::stack<Emitter*> recycledEmitters;
	std::list<Emitter*> activeEmitters;

public:
	EmitterPool() = default;
	EmitterPool(const EmitterPool&) = delete;
	EmitterPool& operator=(const EmitterPool&) = delete;
	~EmitterPool();

	Emitter* getEmitter();
	void returnEmitter(Emitter* b);
};

#endif _EmitterPool
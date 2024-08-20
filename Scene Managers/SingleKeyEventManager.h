#ifndef _SingleKeyEventManager
#define _SingleKeyEventManager

#include "AzulCore.h"
#include <list>
#include "EventTypeEnum.h"

class Inputable;
class SingleKeyEventManager
{
private:
	enum KeyState { KEY_UP, KEY_DOWN };

	AZUL_KEY key;
	KeyState state;

	using InputList = std::list<Inputable*>;

	InputList pressList;
	InputList heldDownList;
	InputList releaseList;
	InputList heldUpList;

public:
	SingleKeyEventManager(AZUL_KEY k);
	SingleKeyEventManager(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager& operator=(const SingleKeyEventManager&) = delete;
	~SingleKeyEventManager() = default;

	using ListRef = InputList::iterator;

	void Register(Inputable* input, EventType::EVENT_TYPE ev, ListRef& ref);
	void Deregister(EventType::EVENT_TYPE ev, ListRef ref);

	void ProcessKeyEvent();
};

#endif _SingleKeyEventManager
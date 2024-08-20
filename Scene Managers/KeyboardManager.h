#ifndef _KeyboardManager
#define _KeyboardManager

#include "SingleKeyEventManager.h"
#include "EventTypeEnum.h"
#include <map>

class Inputable;
class KeyboardManager
{
private:
	using KeyManagerMap = std::map<AZUL_KEY, SingleKeyEventManager*>;
	using KeyMapIterator = KeyManagerMap::iterator;

	using KeyManagerPair = std::pair<AZUL_KEY, SingleKeyEventManager*>;

	KeyManagerMap keyMap;

public:
	KeyboardManager() = default;
	KeyboardManager(const KeyboardManager&) = delete;
	KeyboardManager& operator=(const KeyboardManager&) = delete;
	~KeyboardManager();

	void Register(Inputable*, AZUL_KEY k, EventType::EVENT_TYPE ev, SingleKeyEventManager::ListRef &ref);
	void Deregister(AZUL_KEY k, EventType::EVENT_TYPE ev, SingleKeyEventManager::ListRef ref);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void KeyboardManager::ProcessKeyEvents();
	///
	/// \brief	Process the key events
	/// 
	/// Called once per frame. Only checks keys that objects have registered for.
	///-------------------------------------------------------------------------------------------------

	void ProcessKeyEvents();
};

#endif _KeyboardManager
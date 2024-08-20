#include "KeyboardManager.h"

void KeyboardManager::Register(Inputable* input, AZUL_KEY k, EventType::EVENT_TYPE ev, SingleKeyEventManager::ListRef &ref)
{
	if (keyMap.count(k) == 0)
	{
		SingleKeyEventManager* newManager = new SingleKeyEventManager(k);

		KeyManagerPair pair = KeyManagerPair(k, newManager);
		keyMap.insert(pair);

		newManager->Register(input, ev, ref);
	}
	else
	{
		keyMap.at(k)->Register(input, ev, ref);
	}
}

void KeyboardManager::Deregister(AZUL_KEY k, EventType::EVENT_TYPE ev, SingleKeyEventManager::ListRef ref)
{
	keyMap.at(k)->Deregister(ev, ref);
}

void KeyboardManager::ProcessKeyEvents()
{
	KeyMapIterator it;
	for (it = keyMap.begin(); it != keyMap.end(); it++)
	{
		it->second->ProcessKeyEvent();
	}
}

KeyboardManager::~KeyboardManager()
{
	KeyMapIterator it;
	for (it = keyMap.begin(); it != keyMap.end(); it++)
	{
		delete it->second;
	}
}
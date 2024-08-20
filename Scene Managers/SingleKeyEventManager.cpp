#include "InputableAttorney.h"
#include "SingleKeyEventManager.h"

SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY k)
	:key(k)
{
	state = KeyState::KEY_UP;
}

void SingleKeyEventManager::Register(Inputable* input, EventType::EVENT_TYPE ev, SingleKeyEventManager::ListRef &ref)
{
	switch (ev)
	{
	case(EventType::EVENT_TYPE::KEY_HELD_DOWN):
		ref = heldDownList.insert(heldDownList.end(), input);
		break;
	case(EventType::EVENT_TYPE::KEY_HELD_UP):
		ref = heldUpList.insert(heldUpList.end(), input);
		break;
	case(EventType::EVENT_TYPE::KEY_PRESSED):
		ref = pressList.insert(pressList.end(), input);
		break;
	case(EventType::EVENT_TYPE::KEY_RELEASED):
		ref = releaseList.insert(releaseList.end(), input);
		break;
	default:
		assert(false && "Error while registering for input: Invalid EVENT_TYPE given!");
	}
}

void SingleKeyEventManager::Deregister(EventType::EVENT_TYPE ev, SingleKeyEventManager::ListRef ref)
{
	switch (ev)
	{
	case(EventType::EVENT_TYPE::KEY_HELD_DOWN):
		heldDownList.erase(ref);
		break;
	case(EventType::EVENT_TYPE::KEY_HELD_UP):
		heldUpList.erase(ref);
		break;
	case(EventType::EVENT_TYPE::KEY_PRESSED):
		pressList.erase(ref);
		break;
	case(EventType::EVENT_TYPE::KEY_RELEASED):
		releaseList.erase(ref);
		break;
	default:
		assert(false && "Error while deregistering for input: Invalid EVENT_TYPE given!");
	}
}

void SingleKeyEventManager::ProcessKeyEvent()
{
	if (Keyboard::GetKeyState(key))
	{
		if (state == KeyState::KEY_UP) 
		{
			state = KeyState::KEY_DOWN;
			ListRef it;
			for (it = pressList.begin(); it != pressList.end(); it++)
			{
				InputableAttorney::InputLoop::KeyPressed(*it, key);
			}
		}
		else
		{
			ListRef it;
			for (it = heldDownList.begin(); it != heldDownList.end(); it++)
			{
				InputableAttorney::InputLoop::KeyHeldDown(*it, key);
			}
		}
	}
	else
	{
		if (state == KeyState::KEY_DOWN)
		{
			state = KeyState::KEY_UP;
			ListRef it;
			for (it = releaseList.begin(); it != releaseList.end(); it++)
			{
				InputableAttorney::InputLoop::KeyReleased(*it, key);
			}
		}
		else
		{
			ListRef it;
			for (it = heldUpList.begin(); it != heldUpList.end(); it++)
			{
				InputableAttorney::InputLoop::KeyHeldUp(*it, key);
			}
		}
	}
}
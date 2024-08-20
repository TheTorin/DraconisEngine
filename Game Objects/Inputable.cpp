#include "Inputable.h"
#include "InputableRegisterCmd.h"
#include "InputableDeregisterCmd.h"
#include "SceneBaseAttorney.h"
#include "SceneManager.h"

void Inputable::SubmitInputRegistration(AZUL_KEY k, EventType::EVENT_TYPE ev)
{
	KeyEventPair pair = KeyEventPair(k, ev);
	if (keyMap.count(pair) == 0)
	{
		RegistrationData* newData = new RegistrationData;
		newData->regState = RegistrationStates::PENDING_REGISTRATION;
		newData->pRegister = new InputableRegisterCmd(this, k, ev);
		newData->pDeregister = new InputableDeregisterCmd(this, k, ev);
		keyMap.insert(KeyRegistrationMapPair(pair, newData));

		SceneBaseAttorney::InputRegistration::SubmitCommand(SceneManager::getCurrentScene(), newData->pRegister);
	}
	else
	{
		RegistrationData* regData = keyMap.at(pair);
		assert(regData->regState == RegistrationStates::CURRENTLY_DEREGISTERED);
		SceneBaseAttorney::InputRegistration::SubmitCommand(SceneManager::getCurrentScene(), regData->pRegister);
		regData->regState = RegistrationStates::PENDING_REGISTRATION;
	}
}

void Inputable::InputRegistration(AZUL_KEY k, EventType::EVENT_TYPE ev)
{
	RegistrationData* regData = keyMap.at(KeyEventPair(k, ev));

	assert(regData->regState == RegistrationStates::PENDING_REGISTRATION);
	SceneBaseAttorney::InputRegistration::Register(SceneManager::getCurrentScene(), this, k, ev, regData->pDeleteRef);
	regData->regState = RegistrationStates::CURRENTLY_REGISTERED;
}

void Inputable::SubmitInputDeregistration(AZUL_KEY k, EventType::EVENT_TYPE ev)
{
	KeyEventPair pair = KeyEventPair(k, ev);
	if (keyMap.count(pair) == 0) assert(false && "ERROR! Faulty key and event type passed in to gameObject! Cannot deregister the given key + event pair, as it does not exist!\n");
	else
	{
		RegistrationData* regData = keyMap.at(pair);

		assert(regData->regState == RegistrationStates::CURRENTLY_REGISTERED);
		SceneBaseAttorney::InputRegistration::SubmitCommand(SceneManager::getCurrentScene(), regData->pDeregister);
		regData->regState = RegistrationStates::PENDING_DEREGISTRATION;
	}
}

void Inputable::InputDeregistration(AZUL_KEY k, EventType::EVENT_TYPE ev)
{
	RegistrationData* regData = keyMap.at(KeyEventPair(k, ev));

	assert(regData->regState == RegistrationStates::PENDING_DEREGISTRATION);
	SceneBaseAttorney::InputRegistration::Deregister(SceneManager::getCurrentScene(), k, ev, regData->pDeleteRef);
	regData->regState = RegistrationStates::CURRENTLY_DEREGISTERED;
}

Inputable::~Inputable()
{
	KeyRegistrationMap::iterator it;
	for (it = keyMap.begin(); it != keyMap.end(); it++)
	{
		delete (*it).second->pDeregister;
		delete (*it).second->pRegister;
		delete (*it).second;
	}
}
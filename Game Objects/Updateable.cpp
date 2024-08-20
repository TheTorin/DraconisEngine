#include "Updateable.h"
#include "UpdateRegisterCmd.h"
#include "UpdateDeregisterCmd.h"
#include "SceneManager.h"
#include "SceneBaseAttorney.h"

Updateable::Updateable()
{
	regState = RegistrationStates::CURRENTLY_DEREGISTERED;
	pRegister = new UpdateRegisterCmd(this);
	pDeregister = new UpdateDeregisterCmd(this);
}

void Updateable::SubmitUpdateRegistration()
{
	assert(regState == RegistrationStates::CURRENTLY_DEREGISTERED);
	//OutputDebugString("Registering...");
	SceneBaseAttorney::UpdateRegistration::SubmitCommand(SceneManager::getCurrentScene(), pRegister);
	regState = RegistrationStates::PENDING_REGISTRATION;
}

void Updateable::UpdateRegistration()
{
	assert(regState == RegistrationStates::PENDING_REGISTRATION);
	//OutputDebugString("Registered!");
	SceneBaseAttorney::UpdateRegistration::Register(SceneManager::getCurrentScene(), this, pDeleteRef);
	regState = RegistrationStates::CURRENTLY_REGISTERED;
}

void Updateable::SubmitUpdateDeregistration()
{
	assert(regState == RegistrationStates::CURRENTLY_REGISTERED);
	//OutputDebugString("Deregistering...");
	SceneBaseAttorney::UpdateRegistration::SubmitCommand(SceneManager::getCurrentScene(), pDeregister);
	regState = RegistrationStates::PENDING_DEREGISTRATION;
}

void Updateable::UpdateDeregistration()
{
	assert(regState == RegistrationStates::PENDING_DEREGISTRATION);
	//OutputDebugString("Unregistered!");
	SceneBaseAttorney::UpdateRegistration::Deregister(SceneManager::getCurrentScene(), pDeleteRef);
	regState = RegistrationStates::CURRENTLY_DEREGISTERED;
}

Updateable::~Updateable()
{
	delete pRegister;
	delete pDeregister;
}
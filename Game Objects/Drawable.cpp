#include "Drawable.h"
#include "DrawRegisterCmd.h"
#include "DrawDeregisterCmd.h"
#include "SceneManager.h"
#include "SceneBaseAttorney.h"

Drawable::Drawable()
{
	regState = RegistrationStates::CURRENTLY_DEREGISTERED;
	pRegister = new DrawRegisterCmd(this);
	pDeregister = new DrawDeregisterCmd(this);
}

void Drawable::SubmitDrawRegistration()
{
	assert(regState == RegistrationStates::CURRENTLY_DEREGISTERED);
	SceneBaseAttorney::DrawRegistration::SubmitCommand(SceneManager::getCurrentScene(), pRegister);
	regState = RegistrationStates::PENDING_REGISTRATION;
}

void Drawable::DrawRegistration()
{
	assert(regState == RegistrationStates::PENDING_REGISTRATION);
	SceneBaseAttorney::DrawRegistration::Register(SceneManager::getCurrentScene(), this, pDeleteRef);
	regState = RegistrationStates::CURRENTLY_REGISTERED;
}

void Drawable::SubmitDrawDeregistration()
{
	assert(regState == RegistrationStates::CURRENTLY_REGISTERED);
	SceneBaseAttorney::DrawRegistration::SubmitCommand(SceneManager::getCurrentScene(), pDeregister);
	regState = RegistrationStates::PENDING_DEREGISTRATION;
}

void Drawable::DrawDeregistration()
{
	assert(regState == RegistrationStates::PENDING_DEREGISTRATION);
	SceneBaseAttorney::DrawRegistration::Deregister(SceneManager::getCurrentScene(), pDeleteRef);
	regState = RegistrationStates::CURRENTLY_DEREGISTERED;
}

Drawable::~Drawable()
{
	delete pRegister;
	delete pDeregister;
}
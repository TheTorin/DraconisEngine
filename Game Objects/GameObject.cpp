#include "GameObject.h"
#include "GameObjectEnterCmd.h"
#include "GameObjectExitCmd.h"
#include "SceneBaseAttorney.h"
#include "SceneManager.h"

GameObject::GameObject()
{
	regState = RegistrationStates::CURRENTLY_DEREGISTERED;
	enterCmd = new GameObjectEnterCmd(this);
	exitCmd = new GameObjectExitCmd(this);
}

void GameObject::SubmitEntry()
{
	assert(regState == RegistrationStates::CURRENTLY_DEREGISTERED);
	SceneBaseAttorney::SceneEnterExit::SubmitCommand(SceneManager::getCurrentScene(), enterCmd);
	regState = RegistrationStates::PENDING_REGISTRATION;
}

void GameObject::ConnectToScene()
{
	assert(regState == RegistrationStates::PENDING_REGISTRATION);
	regState = RegistrationStates::CURRENTLY_REGISTERED;

	this->SceneEntry();
}

void GameObject::SubmitExit()
{
	if (regState != RegistrationStates::CURRENTLY_REGISTERED) return;
	SceneBaseAttorney::SceneEnterExit::SubmitCommand(SceneManager::getCurrentScene(), exitCmd);
	regState = RegistrationStates::PENDING_DEREGISTRATION;
}

void GameObject::DisconnectFromScene()
{
	regState = RegistrationStates::CURRENTLY_DEREGISTERED;

	this->SceneExit();
}

GameObject::~GameObject()
{
	delete enterCmd;
	delete exitCmd;
}
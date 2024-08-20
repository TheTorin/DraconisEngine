#include "Collidable.h"
#include "CollisionRegisterCmd.h"
#include "CollisionDeregisterCmd.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "SceneManager.h"

Collidable::Collidable()
{
	regState = RegistrationStates::CURRENTLY_DEREGISTERED;
	pRegister = new CollisionRegisterCmd(this);
	pDeregister = new CollisionDeregisterCmd(this);
	defaultSphere = new CollisionVolumeBSphere();
	colVolume = nullptr;
}

void Collidable::SubmitCollisionRegistration()
{
	assert(regState == RegistrationStates::CURRENTLY_DEREGISTERED);
	SceneBaseAttorney::CollisionRegistration::SubmitCommand(SceneManager::getCurrentScene(), pRegister);
	regState = RegistrationStates::PENDING_REGISTRATION;
}

void Collidable::CollisionRegistration()
{
	assert(regState == RegistrationStates::PENDING_REGISTRATION);
	SceneBaseAttorney::CollisionRegistration::GetColManager(SceneManager::getCurrentScene())->GetColGroup(myID)->Register(this, pDeleteRef);
	regState = RegistrationStates::CURRENTLY_REGISTERED;
}

void Collidable::SubmitCollisionDeregistration()
{
	if (regState != RegistrationStates::CURRENTLY_REGISTERED) return;
	SceneBaseAttorney::CollisionRegistration::SubmitCommand(SceneManager::getCurrentScene(), pDeregister);
	regState = RegistrationStates::PENDING_DEREGISTRATION;
}

void Collidable::CollisionDeregistration()
{
	assert(regState == RegistrationStates::PENDING_DEREGISTRATION);
	SceneBaseAttorney::CollisionRegistration::GetColManager(SceneManager::getCurrentScene())->GetColGroup(myID)->Deregister(pDeleteRef);
	regState = RegistrationStates::CURRENTLY_DEREGISTERED;
}

const CollisionVolume* Collidable::GetCollisionVolume()
{
	return colVolume;
}

void Collidable::SetColliderModel(Model* m, VolumeType vol)
{
	pModel = m;
	if (vol == VolumeType::BSPHERE) colVolume = defaultSphere;
	else if (vol == VolumeType::AABB) colVolume = new CollisionVolumeAABB();
	else if (vol == VolumeType::OBB) colVolume = new CollisionVolumeOBB();
}

void Collidable::UpdateCollisionData(const Matrix& m)
{
	colVolume->ComputeData(pModel, m);
	defaultSphere->ComputeData(pModel, m);
}

Collidable::~Collidable()
{
	delete pRegister;
	delete pDeregister;
	if (colVolume != nullptr && colVolume != defaultSphere) delete colVolume;
	delete defaultSphere;
}
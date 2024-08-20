#ifndef _Updateable
#define _Updateable

#include "RegistrationStates.h"
#include "UpdateableManager.h"

class UpdateRegisterCmd;
class UpdateDeregisterCmd;

class Updateable
{
	friend class UpdateableAttorney;
private:
	RegistrationStates regState;
	UpdateRegisterCmd* pRegister;
	UpdateDeregisterCmd* pDeregister;
	UpdateableManager::ListRef pDeleteRef;

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Updateable::Update()
	/// \ingroup ENGINE_CALLED_EVENTS
	/// 
	/// \brief	Called every Update frame
	///-------------------------------------------------------------------------------------------------

	virtual void Update() {};

	void UpdateRegistration();
	void UpdateDeregistration();

public:
	Updateable();
	Updateable(const Updateable&) = delete;
	Updateable& operator=(const Updateable&) = delete;
	virtual ~Updateable();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Updateable::SubmitUpdateRegistration();
	/// \ingroup (DE)REGISTRATION_EVENTS
	/// 
	/// \brief	Submits update registration for this object
	///-------------------------------------------------------------------------------------------------

	void SubmitUpdateRegistration();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Updateable::SubmitUpdateDeregistration();
	/// \ingroup (DE)REGISTRATION_EVENTS
	/// 
	/// \brief	Submit update deregistration for this object
	///-------------------------------------------------------------------------------------------------

	void SubmitUpdateDeregistration();
};

#endif _Updateable
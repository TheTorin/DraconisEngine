#ifndef _Drawable
#define _Drawable

#include "RegistrationStates.h"
#include "DrawableManager.h"

class DrawRegisterCmd;
class DrawDeregisterCmd;

class Drawable
{
	friend class DrawableAttorney;
private:
	RegistrationStates regState;
	DrawRegisterCmd* pRegister;
	DrawDeregisterCmd* pDeregister;
	DrawableManager::ListRef pDeleteRef;

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Drawable::Draw()
	/// \ingroup ENGINE_CALLED_EVENTS
	///
	/// \brief	Code that is called during the Draw step of the engine
	///-------------------------------------------------------------------------------------------------

	virtual void Draw() {};

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Drawable::Draw2D() = 0;
	/// \ingroup ENGINE_CALLED_EVENTS
	///
	/// \brief	Code called during the Draw step, specifically for drawing all 2D sprites / images.
	/// 		
	/// This occurs AFTER Draw()
	///-------------------------------------------------------------------------------------------------

	virtual void Draw2D() {};

	void DrawRegistration();
	void DrawDeregistration();

public:
	Drawable();
	Drawable(const Drawable&) = delete;
	Drawable& operator=(const Drawable&) = delete;
	virtual ~Drawable();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Drawable::SubmitDrawRegistration();
	/// \ingroup (DE)REGISTRATION_EVENTS
	/// 
	/// \brief	Submit draw registration for this object
	///-------------------------------------------------------------------------------------------------

	void SubmitDrawRegistration();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Drawable::SubmitDrawDeregistration();
	/// \ingroup (DE)REGISTRATION_EVENTS
	/// 
	/// \brief	Submit draw deregistration for this object
	///-------------------------------------------------------------------------------------------------

	void SubmitDrawDeregistration();
};

#endif _Drawable
#ifndef _Inputable
#define _Inputable

#include "RegistrationStates.h"
#include "AzulCore.h"
#include "EventTypeEnum.h"
#include "SingleKeyEventManager.h"
#include <map>

class InputableRegisterCmd;
class InputableDeregisterCmd;

class Inputable
{
	friend class InputableAttorney;
private:
	struct RegistrationData {
		RegistrationStates regState;
		InputableRegisterCmd* pRegister;
		InputableDeregisterCmd* pDeregister;
		SingleKeyEventManager::ListRef pDeleteRef;
	};

	using KeyEventPair = std::pair<AZUL_KEY, EventType::EVENT_TYPE>;
	using KeyRegistrationMap = std::map<KeyEventPair, RegistrationData*>;
	using KeyRegistrationMapPair = std::pair<KeyEventPair, RegistrationData*>;

	KeyRegistrationMap keyMap;

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Inputable::KeyPressed(AZUL_KEY k)
	/// \ingroup ENGINE_CALLED_EVENTS
	///
	/// \brief	Function called if one of the keys the object registered has been pressed
	///
	/// \param 	k	The AZUL_KEY that was pressed.
	///-------------------------------------------------------------------------------------------------

	virtual void KeyPressed(AZUL_KEY k) { k; };

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Inputable::KeyHeldDown(AZUL_KEY k)
	/// \ingroup ENGINE_CALLED_EVENTS
	///
	/// \brief	Function called if one of the keys the object registered has been held
	///
	/// \param 	k	The AZUL_KEY that was held.
	///-------------------------------------------------------------------------------------------------

	virtual void KeyHeldDown(AZUL_KEY k) { k; };

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Inputable::KeyReleased(AZUL_KEY k)
	/// \ingroup ENGINE_CALLED_EVENTS
	/// 
	/// \brief	Function called if one of the keys the object registered has been released
	///
	/// \param 	k	The AZUL_KEY that was released.
	///-------------------------------------------------------------------------------------------------

	virtual void KeyReleased(AZUL_KEY k) { k; };

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Inputable::KeyHeldUp(AZUL_KEY k)
	/// \ingroup ENGINE_CALLED_EVENTS
	/// 
	/// \brief	Function called if one of the keys the object registered has been held up (has not been touched)
	///
	/// \param 	k	The AZUL_KEY that was held up.
	///-------------------------------------------------------------------------------------------------

	virtual void KeyHeldUp(AZUL_KEY k) { k; };

	void InputRegistration(AZUL_KEY k, EventType::EVENT_TYPE ev);
	void InputDeregistration(AZUL_KEY k, EventType::EVENT_TYPE ev);

public:
	Inputable() = default;
	Inputable(const Inputable&) = delete;
	Inputable& operator=(const Inputable&) = delete;
	virtual ~Inputable();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Inputable::SubmitInputRegistration(AZUL_KEY k, EventType::EVENT_TYPE ev);
	/// \ingroup (DE)REGISTRATION_EVENTS
	/// 
	/// \brief	Submit input registration for the object, given the key and event
	///
	/// \param 	k 	An AZUL_KEY to process. Key is chosen through AZUL_KEY::key
	/// \param 	ev	The event type to process. There are four events.
	/// 			
	/// \par Event Types:
	/// 	 
	/// 	 There are four event types within the engine currently:
	/// 	 
	/// 	 KeyPressed is called on the first frame that the key is pressed. It will not be called again until the key is released and pressed again.
	/// 	 KeyHeldDown is NOT called on the first frame that the key is pressed, however it is called on every frame after until the key is released
	/// 	 KeyReleased is called on the first frame that the key is released. It will not be called again until the key is pressed and released again.
	/// 	 KeyHeldUp is NOT called on the first frame that the key is released, however it is called on every frame after until the key is pressed.
	///-------------------------------------------------------------------------------------------------

	void SubmitInputRegistration(AZUL_KEY k, EventType::EVENT_TYPE ev);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Inputable::SubmitInputDeregistration(AZUL_KEY k, EventType::EVENT_TYPE ev);
	/// \ingroup (DE)REGISTRATION_EVENTS
	/// 
	/// \brief	Submit input deregistration. Will throw an error if the given key/event combination is not found.
	///
	/// \param 	k 	An AZUL_KEY to process.
	/// \param 	ev	The ev.
	///-------------------------------------------------------------------------------------------------

	void SubmitInputDeregistration(AZUL_KEY k, EventType::EVENT_TYPE ev);
};

#endif _Inputable
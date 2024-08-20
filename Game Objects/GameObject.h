#ifndef _GameObject
#define _GameObject

#include "Drawable.h"
#include "Updateable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "Collidable.h"

#include "SpriteFontManager.h"
#include "ImageManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"

class GameObjectEnterCmd;
class GameObjectExitCmd;
class GameObject : public Updateable, public Drawable, public Alarmable, public Inputable, public Collidable
{
	friend class GameObjectAttorney;
private:
	RegistrationStates regState;
	GameObjectEnterCmd* enterCmd;
	GameObjectExitCmd* exitCmd;

	void ConnectToScene();
	void DisconnectFromScene();

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void GameObject::SceneEntry()
	/// 
	/// \brief	Called when the object is first entering the scene after SubmitEntry() is called.
	/// \ingroup ENGINE_CALLED_EVENTS
	/// 		
	/// All registrations should be contained within this function, if SubmitEntry() is being used.
	/// The constructor should be used for all other initializations, such as setting up the model, shader, e.t.c
	///-------------------------------------------------------------------------------------------------

	virtual void SceneEntry() {};

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void GameObject::SceneExit()
	/// 
	/// \brief	Called when the object is about to leave the scene after SubmitExit() is called
	/// \ingroup ENGINE_CALLED_EVENTS
	/// 		 
	/// In this function, the GameObject must be deregistered from EVERYTHING in order to prevent errors.
	/// This includes input and alarms.
	///-------------------------------------------------------------------------------------------------

	virtual void SceneExit() {};

public:
	GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	virtual ~GameObject();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void GameObject::SubmitEntry();
	///
	/// \brief	Submits entry for this object into the current scene. Enters on the following frame.
	/// \ingroup (DE)REGISTRATION_EVENTS
	/// 
	/// This function should be used if the object gets spawned in / out multiple times, such as bullets in a factory pool.
	/// If the object will only be used once and will not be recycled, this function should likely not be used.
	/// This will have to be called by a different object, as this object should not be on the Update/Alarm list at that time
	/// 
	///-------------------------------------------------------------------------------------------------

	void SubmitEntry();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void GameObject::SubmitExit();
	/// 
	/// \brief	Submits exit for this object out of the current scene. Exits on the following frame.
	/// \ingroup (DE)REGISTRATION_EVENTS
	/// 
	/// Unlike SubmitEntry(), SubmitExit() can be called by the current object.
	///-------------------------------------------------------------------------------------------------

	void SubmitExit();
};

#endif _GameObject
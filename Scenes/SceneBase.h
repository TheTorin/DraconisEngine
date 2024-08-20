#ifndef _SceneBase
#define _SceneBase

#include "UpdateableManager.h"
#include "DrawableManager.h"
#include "AlarmableManager.h"
#include "KeyboardManager.h"
#include "CollisionManager.h"
#include "SceneBroker.h"
#include "EventTypeEnum.h"
#include "CameraManager.h"
#include "TerrainManager.h"
#include "TerrainSceneManager.h"

class Terrain;
class Scene
{
	friend class SceneBaseAttorney;
private:
	CameraManager camManager;
	UpdateableManager updateManager;
	DrawableManager drawManager;
	AlarmableManager alarmManager;
	KeyboardManager keyManager;
	CollisionManager colManager;
	SceneBroker broker;
	TerrainSceneManager tManager;

	void SubmitCommand(SceneCommandBase* cmd);

	void Register(Updateable* up, UpdateableManager::ListRef& ref);
	void Register(Drawable* draw, DrawableManager::ListRef& ref);
	void Register(float time, Alarmable* alarm, AlarmableManager::ALARM_ID id, AlarmableManager::ListRef& ref);
	void Register(Inputable* input, AZUL_KEY k, EventType::EVENT_TYPE ev, SingleKeyEventManager::ListRef& ref);

	void Deregister(UpdateableManager::ListRef ref);
	void Deregister(DrawableManager::ListRef ref);
	void Deregister(AlarmableManager::ListRef ref);
	void Deregister(AZUL_KEY k, EventType::EVENT_TYPE ev, SingleKeyEventManager::ListRef ref);

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Scene::Initialize()
	///
	/// \brief	Initializes the scene. This is only called once when the scene is starting up.
	/// 		
	/// This is where everything should be created. Factories / Managers should be initialized, and collision pairs / selfs should be set here too
	/// 
	/// Unlike Draw() or Update(), the base Initialize does not need to be called, as it is empty.
	///-------------------------------------------------------------------------------------------------

	virtual void Initialize() {};

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Scene::Update();
	///
	/// \brief	Updates the scene. Typically does not need code
	/// 
	/// Important: If this function is overridden, the base Update() MUST be called, or objects will not update
	/// 
	/// The execution order of each Scene follows the following order:
	/// 1. All registration/deregistration commands are processed  
	/// 2. Alarms are checked and, if relevant, triggered  
	/// 3. Keyboard input is checked for all registered keys  
	/// 4. The Update() function on all registered objects is called  
	/// 5. All registered collisions are checked
	///-------------------------------------------------------------------------------------------------

	virtual void Update();

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Scene::Draw();
	///
	/// \brief	Draws the scene. Typically does not need code
	///
	/// The scene is drawn in the following order:
	/// 1. All 3D objects that are registered
	/// 2. All Visualizer commands are processed  
	/// 3. All 2D objects that are registered  
	///
	/// Important: In order to be rendered correctly, sprites must be attached to a gameObject,
	/// and the sprite Render() function must be called in the Draw2D() function. The Draw2D() function
	/// will only be called if the gameObject itself is registered via SubmitDrawRegistration()
	/// 
	/// Also, if this function is override, the base class Draw() MUST be called, or objects will not be drawn
	///-------------------------------------------------------------------------------------------------

	virtual void Draw();

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Scene::Draw2D();
	///
	/// \brief	Deprecated. No longer used by the engine.
	/// 
	/// This function is not to be confused with GameObject::Draw2D(), which is still in use.
	///-------------------------------------------------------------------------------------------------

	virtual void Draw2D();

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Scene::SceneEnd()
	///
	/// \brief	Ends the scene. This is called before the scene changes
	/// 
	/// Everything should be deleted / terminated here.
	/// 
	/// Unlike Draw() or Update(), the base SceneEnd() does not need to be called, as it is empty.
	///-------------------------------------------------------------------------------------------------

	virtual void SceneEnd() {};

protected:

	///-------------------------------------------------------------------------------------------------
	/// \fn	template <typename C1, typename C2> void Scene::SetCollisionPair()
	///
	/// \brief	Activates collisions between the two given types
	///
	/// \tparam	C1	Type of the c 1.
	/// \tparam	C2	Type of the c 2.
	///-------------------------------------------------------------------------------------------------

	template <typename C1, typename C2> void SetCollisionPair()
	{
		colManager.SetCollisionPair<C1, C2>();
	}

	///-------------------------------------------------------------------------------------------------
	/// \fn	template <typename C1> void Scene::SetCollisionSelf()
	///
	/// \brief	Activates collisions between objects of the same type
	///
	/// An object will not collide with itself
	/// 
	/// \tparam	C1	Type of the c 1.
	///-------------------------------------------------------------------------------------------------

	template <typename C1> void SetCollisionSelf()
	{
		colManager.SetCollisionSelf<C1>();
	}

	template <typename C1> void SetCollisionTerrain()
	{
		colManager.SetCollisionTerrain<C1>();
	}

	void SetTerrain(Terrain* t) { tManager.SetTerrain(t); };

public:
	Scene() = default;
	Scene(const Scene&) = default;
	Scene& operator=(const Scene&) = default;
	~Scene() = default;

	///-------------------------------------------------------------------------------------------------
	/// \fn	Camera* Scene::getCurrentCamera()
	///
	/// \brief	Gets current camera
	///
	/// \returns	Null if it fails, else the camera used to render 3D objects.
	///-------------------------------------------------------------------------------------------------

	Camera* getCurrentCamera() { return camManager.getCurrentCamera(); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	Camera* Scene::get2DCamera()
	///
	/// \brief	Gets 2D camera
	///
	/// \returns	Null if it fails, else the camera used to render 2D objects.
	///-------------------------------------------------------------------------------------------------

	Camera* get2DCamera() { return camManager.get2DCamera(); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Scene::setCurrentCamera(Camera* cam)
	///
	/// \brief	Sets current camera to the given one
	///
	/// \param [in,out]	cam	If non-null, the camera that will be used to render 3D objects.
	///-------------------------------------------------------------------------------------------------

	void setCurrentCamera(Camera* cam) { camManager.setCurrentCamera(cam); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Scene::setGodCam()
	///
	/// \brief	Sets god camera as the current camera
	/// 
	/// \par Controls:
	/// 	 I, J, K, L : Controls where the camera looks
	/// 	 Arrow keys : Controls the left/right and up/down movement of the camera
	/// 	 Page Up/Down : Zooms the camera in or out
	///-------------------------------------------------------------------------------------------------

	void setGodCam() { camManager.setGodCamAsCurrent(); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Scene::setDefaultCam()
	///
	/// \brief	Sets the default camera as the current camera
	///-------------------------------------------------------------------------------------------------

	void setDefaultCam() { camManager.setDefaultAsCurrent(); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	Terrain* Scene::GetTerrain()
	///
	/// \brief	Returns the Terrain used for the current scene
	///-------------------------------------------------------------------------------------------------

	Terrain* GetTerrain() { return tManager.GetTerrain(); };
};

#endif _SceneBase
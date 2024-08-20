#ifndef _SceneManager
#define _SceneManager

#include "SceneBase.h"
#include "SceneNull.h"
#include "SceneChangeCmd.h"
#include "SceneChangeNullCmd.h"

class SceneManager
{
	friend class SceneManagerAttorney;
private:
	static SceneManager* ptrInstance;

	SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	~SceneManager();

	static SceneManager& Instance()
	{
		if (!ptrInstance)
		{
			ptrInstance = new SceneManager();
		}
		return *ptrInstance;
	}

	Scene* ptrStartScene;
	Scene* ptrCurrentScene;

	SceneChangeCmd changeCmd;
	SceneChangeNull nullCmd;

	SceneChangeBase* ptrCurrentCmd;

	Scene* privGetCurrentScene() { return ptrCurrentScene; };
	void privSetStartScene(Scene* ns);
	void privInitStartScene();

	void privSetNextScene(Scene* ns);
	void changeScene(Scene* ns);

	void privUpdate();
	void privDraw();
	void privDraw2D();

	static void initStartScene() { Instance().privInitStartScene(); };
	static void Update() { Instance().privUpdate(); };
	static void Draw() { Instance().privDraw(); };
	static void Draw2D() { Instance().privDraw2D(); };
	static void Terminate();

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static Scene* SceneManager::getCurrentScene()
	/// \ingroup INFO
	/// 
	/// \brief	Gets current scene
	///
	/// \returns	Null if it fails, else the current scene.
	///-------------------------------------------------------------------------------------------------

	static Scene* getCurrentScene() { return Instance().privGetCurrentScene(); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void SceneManager::setStartScene(Scene* ns)
	///
	/// \brief	Sets start scene. Done within the LoadAllResources file typically
	///
	/// \param [in,out]	ns	If non-null, the scene the game will start on.
	///-------------------------------------------------------------------------------------------------

	static void setStartScene(Scene* ns) { Instance().privSetStartScene(ns); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void SceneManager::setNextScene(Scene* ns)
	///
	/// \brief	Changes the scene to the given next scene. Will swap on the next frame.
	///
	/// \param [in,out]	ns	If non-null, the scene to change to.
	///-------------------------------------------------------------------------------------------------

	static void setNextScene(Scene* ns) { Instance().privSetNextScene(ns); };
};

#endif _SceneManager
#include "SceneManager.h"
#include "SceneBaseAttorney.h"
#include "SceneChangeCmd.h"
#include "SceneChangeNullCmd.h"

SceneManager* SceneManager::ptrInstance = nullptr;

SceneManager::SceneManager()
{
	ptrStartScene = new SceneNull();
	ptrCurrentScene = ptrStartScene;
	ptrCurrentCmd = &nullCmd;
}

void SceneManager::privSetStartScene(Scene* ns)
{
	delete ptrStartScene;
	ptrStartScene = ns;
	ptrCurrentScene = ns;
}

void SceneManager::privInitStartScene()
{
	SceneBaseAttorney::SceneManagement::Initialize(ptrStartScene);
}

void SceneManager::privUpdate()
{
	ptrCurrentCmd->Execute();

	SceneBaseAttorney::SceneManagement::Update(ptrCurrentScene);
}

void SceneManager::privSetNextScene(Scene* ns)
{
	assert(ptrCurrentCmd->getHeldScene() != ns);

	changeCmd.changeHeldScene(ns);
	ptrCurrentCmd = &changeCmd;
}

void SceneManager::changeScene(Scene* ns)
{
	SceneBaseAttorney::SceneManagement::SceneEnd(ptrCurrentScene);
	SceneBaseAttorney::SceneManagement::UninitializeTerrain(ptrCurrentScene);
	delete ptrCurrentScene;
	ptrCurrentScene = ns;
	SceneBaseAttorney::SceneManagement::Initialize(ptrCurrentScene);
	SceneBaseAttorney::SceneManagement::InitializeTerrain(ptrCurrentScene);
	ptrCurrentCmd = &nullCmd;
}

void SceneManager::privDraw()
{
	SceneBaseAttorney::SceneManagement::Draw(ptrCurrentScene);
}

void SceneManager::privDraw2D()
{
	SceneBaseAttorney::SceneManagement::Draw2D(ptrCurrentScene);
}

void SceneManager::Terminate()
{
	SceneBaseAttorney::SceneManagement::SceneEnd(Instance().ptrCurrentScene);
	delete Instance().ptrCurrentScene;
	delete ptrInstance;
	ptrInstance = nullptr;
}

SceneManager::~SceneManager()
{
	if (ptrCurrentCmd == &changeCmd)
	{
		delete changeCmd.getHeldScene();
	}
}
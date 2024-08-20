#ifndef _SceneManagerAttorney
#define _SceneManagerAttorney

#include "SceneManager.h"

class SceneManagerAttorney
{
public:
	class SceneManagement
	{
		friend class Draconis;
	private:
		static void initStartScene() { SceneManager::initStartScene(); };
		static void Update() { SceneManager::Update(); };
		static void Draw() { SceneManager::Draw(); };
		static void Draw2D() { SceneManager::Draw2D(); };
		static void Terminate() { SceneManager::Terminate(); };
	};

	class SceneChanging
	{
		friend class SceneChangeCmd;
	private:
		static void changeScene(Scene* ns) { SceneManager::Instance().changeScene(ns); };
	};
};

#endif _SceneManagerAttorney
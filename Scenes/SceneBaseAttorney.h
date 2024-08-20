#ifndef _SceneBaseAttorney
#define _SceneBaseAttorney

#include "SceneBase.h"

class SceneBaseAttorney 
{
public:
	class UpdateRegistration
	{
		friend class Updateable;
	private:
		static void SubmitCommand(Scene* sc, SceneCommandBase* cmd) { sc->SubmitCommand(cmd); };
		static void Register(Scene* sc, Updateable* up, UpdateableManager::ListRef& ref) { sc->Register(up, ref); };
		static void Deregister(Scene* sc, UpdateableManager::ListRef& ref) { sc->Deregister(ref); };
	};

	class DrawRegistration
	{
		friend class Drawable;
	private:
		static void SubmitCommand(Scene* sc, SceneCommandBase* cmd) { sc->SubmitCommand(cmd); };
		static void Register(Scene* sc, Drawable* draw, DrawableManager::ListRef& ref) { sc->Register(draw, ref); };
		static void Deregister(Scene* sc, DrawableManager::ListRef& ref) { sc->Deregister(ref); };
	};

	class AlarmRegistration
	{
		friend class Alarmable;
	private:
		static void SubmitCommand(Scene* sc, SceneCommandBase* cmd) { sc->SubmitCommand(cmd); };
		static void Register(Scene* sc, float time, Alarmable* alarm, AlarmableManager::ALARM_ID id, AlarmableManager::ListRef& ref) { sc->Register(time, alarm, id, ref); };
		static void Deregister(Scene* sc, AlarmableManager::ListRef& ref) { sc->Deregister(ref); };
	};

	class InputRegistration
	{
		friend class Inputable;
	private:
		static void SubmitCommand(Scene* sc, SceneCommandBase* cmd) { sc->SubmitCommand(cmd); };
		static void Register(Scene* sc, Inputable* input, AZUL_KEY k, EventType::EVENT_TYPE ev, SingleKeyEventManager::ListRef& ref) { sc->Register(input, k, ev, ref); };
		static void Deregister(Scene* sc, AZUL_KEY k, EventType::EVENT_TYPE ev, SingleKeyEventManager::ListRef ref) { sc->Deregister(k, ev, ref); };
	};

	class CollisionRegistration
	{
		friend class Collidable;
	private:
		static void SubmitCommand(Scene* sc, SceneCommandBase* cmd) { sc->SubmitCommand(cmd); };
		static CollisionManager* GetColManager(Scene* sc) { return &sc->colManager; };
	};

	class SceneEnterExit
	{
		friend class GameObject;
	private:
		static void SubmitCommand(Scene* sc, SceneCommandBase* cmd) { sc->SubmitCommand(cmd); };
	};
	
	class SceneManagement
	{
		friend class SceneManager;
	private:
		static void Initialize(Scene* sc) { sc->Initialize(); };
		static void InitializeTerrain(Scene* sc) { sc->tManager.InitializeTerrain(); };
		static void UninitializeTerrain(Scene* sc) { sc->tManager.UninitializeTerrain(); };
		static void Update(Scene* sc) { sc->Update(); };
		static void Draw(Scene* sc) { sc->Draw(); };
		static void Draw2D(Scene* sc) { sc->Draw2D(); };
		static void SceneEnd(Scene* sc) { sc->SceneEnd(); };
	};
};

#endif _SceneBaseAttorney
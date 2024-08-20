#include "SceneBase.h"
#include "VisualizerAttorney.h"

void Scene::Update()
{
	broker.executeCommands();

	alarmManager.ProcessAlarms();

	keyManager.ProcessKeyEvents();

	updateManager.ProcessElements();

	colManager.ProcessCollisions();
}

void Scene::Draw()
{
	drawManager.ProcessElements();

	VisualizerAttorney::Engine::ProcessCommands();

	drawManager.Process2DElements();
}

void Scene::Draw2D()
{
	drawManager.Process2DElements();
}

void Scene::SubmitCommand(SceneCommandBase* cmd)
{
	broker.addCommand(cmd);
}

void Scene::Register(Updateable* up, UpdateableManager::ListRef &ref)
{
	updateManager.Register(up, ref);
}

void Scene::Register(Drawable* draw, DrawableManager::ListRef &ref)
{
	drawManager.Register(draw, ref);
}

void Scene::Register(float time, Alarmable* alarm, AlarmableManager::ALARM_ID id, AlarmableManager::ListRef& ref)
{
	alarmManager.Register(time, alarm, id, ref);
}

void Scene::Register(Inputable* input, AZUL_KEY k, EventType::EVENT_TYPE ev, SingleKeyEventManager::ListRef& ref)
{
	keyManager.Register(input, k, ev, ref);
}

void Scene::Deregister(UpdateableManager::ListRef ref)
{
	updateManager.Deregister(ref);
}

void Scene::Deregister(DrawableManager::ListRef ref)
{
	drawManager.Deregister(ref);
}

void Scene::Deregister(AlarmableManager::ListRef ref)
{
	alarmManager.Deregister(ref);
}

void Scene::Deregister(AZUL_KEY k, EventType::EVENT_TYPE ev, SingleKeyEventManager::ListRef ref)
{
	keyManager.Deregister(k, ev, ref);
}
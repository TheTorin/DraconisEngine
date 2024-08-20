#include "TestScene.h"
#include "BulletFactory.h"
#include "PlayerManager.h"
#include "BotManager.h"
#include "Player.h"

void TestScene::Initialize()
{
	PlayerManager::Initialize();
	BotManager::Initialize();

	SetCollisionSelf<Player>();
}

void TestScene::SceneEnd()
{
	BulletFactory::Terminate();
	BotManager::Terminate();
	PlayerManager::Terminate();
}
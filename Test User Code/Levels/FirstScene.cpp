#include "FirstScene.h"
#include "BotManager.h"
#include "BulletFactory.h"
#include "PlayerManager.h"
#include "Player.h"
#include "AIBot.h"
#include "Bullet.h"
#include "..//DraconisEngine/Draconis.h"
#include "BombFactory.h"
#include "Bomb.h"

void FirstScene::Initialize()
{
	Draconis::setClear(0.4f, 0.4f, 0.8f, 1.0f);
	//SceneManager::getCurrentScene()->setGodCam();

	SetTerrain(TerrainManager::Get("Level1"));

	gobj3 = new BillboardTest();
	gobj4 = new PlaneBot();
	gobj4->Initialize(Matrix(IDENTITY), Vect(0, 100, 0));
	gobj4->SubmitEntry();
	build1 = new Building();
	build1->Set(Vect(300, 0, 300));

	PlayerManager::Initialize();
	BotManager::Initialize();

	gobj1 = new UI();

	SetCollisionPair<Player, Bullet>();
	SetCollisionPair<Player, Bomb>();
	SetCollisionPair<AIBot, Bullet>();
	SetCollisionPair<AIBot, Player>();
	SetCollisionPair<PlaneBot, Bullet>();
	SetCollisionPair<Building, Bullet>();
	SetCollisionPair<Building, Bomb>();
	
	SetCollisionTerrain<Player>();
}

void FirstScene::SceneEnd()
{
	delete gobj1;
	delete gobj3;
	delete gobj4;
	delete build1;

	BulletFactory::Terminate();
	BombFactory::Terminate();
	BotManager::Terminate();
	PlayerManager::Terminate();

	SceneManager::getCurrentScene()->setDefaultCam();
}
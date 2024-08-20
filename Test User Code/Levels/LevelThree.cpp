#include "LevelThree.h"
#include "PlayerManager.h"
#include "Player.h"
#include "..//DraconisEngine/Draconis.h"
#include "Bullet.h"
#include "BulletFactory.h"
#include "BotManager.h"
#include "AIBot.h"
#include "Bomb.h"
#include "PlaneBotManager.h"
#include "PlaneBotFactory.h"
#include "PlaneBot.h"
#include "BombFactory.h"
#include "BuildingManager.h"

void LevelThree::Initialize()
{
	SetTerrain(TerrainManager::Get("Level3"));

	b1 = new Building();
	b1->Set(Vect(0, -500, 0));

	PlayerManager::SetSpawnPosition(Vect(0, 0, -1000));
	PlayerManager::Initialize();

	SetCollisionTerrain<Bullet>();

	BotManager::Initialize();
	
	planeManager = new PlaneBotManager();
	PlaneBotFactory::CreatePlane(Matrix(IDENTITY), Vect(100, 500, 100));

	botSpawner = new AIBotSpawner();

	SetCollisionPair<AIBot, Bomb>();
	SetCollisionPair<Player, Bomb>();
	SetCollisionPair<PlaneBot, Bullet>();
	SetCollisionTerrain<Bomb>();

	boss = new BossBuilding();

	ui = new UI();
	ui->ToggleBossHP();

	SetCollisionPair<Player, Bullet>();
	SetCollisionPair<AIBot, Bullet>();
	SetCollisionPair<Building, Bullet>();
	SetCollisionPair<BossBuilding, Bullet>();
}

void LevelThree::SceneEnd()
{
	delete b1;
	delete ui;
	delete boss;
	delete planeManager;
	delete botSpawner;

	PlayerManager::Terminate();
	BotManager::Terminate();
	BulletFactory::Terminate();
	BombFactory::Terminate();
	BuildingManager::Terminate();
	PlaneBotFactory::Terminate();
}
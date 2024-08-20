#include "LevelTwo.h"
#include "PlayerManager.h"
#include "Player.h"
#include "..//DraconisEngine/Draconis.h"
#include "Bullet.h"
#include "BuildingManager.h"
#include "BulletFactory.h"
#include "BotManager.h"
#include "AIBot.h"
#include "PlaneBotFactory.h"
#include "Bomb.h"
#include "BombFactory.h"
#include "PlaneBot.h"

void LevelTwo::Initialize()
{
	SetTerrain(TerrainManager::Get("Level2"));

	float xDiff = (endX - startX) / BuildingsX;
	float zDiff = (endZ - startZ) / BuildingsZ;

	for (int i = 0; i < BuildingsX; ++i)
	{
		for (int j = 0; j < BuildingsZ; j++)
		{
			Buildings[i * BuildingsZ + j] = new Building();
			Buildings[i * BuildingsZ + j]->Set(Vect(startX + (i * xDiff), 464, startZ + (j * zDiff)));
			float scale = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f))) + 1.0f;
			Buildings[i * BuildingsZ + j]->SetScale(scale);
		}
	}

	PlayerManager::SetSpawnPosition(Vect(1000, 174, -1000));
	PlayerManager::Initialize();

	SetCollisionTerrain<Bullet>();

	BotManager::Initialize();

	PlaneBotFactory::CreatePlane(Matrix(IDENTITY), Vect(-500, 700, -250));
	PlaneBotFactory::CreatePlane(Matrix(IDENTITY), Vect(460, 700, 0));

	ui = new UI();
	ui->ToggleBotsLeft();

	SetCollisionPair<Player, Bullet>();
	SetCollisionPair<AIBot, Bullet>();
	SetCollisionPair<Building, Bullet>();
	SetCollisionPair<PlaneBot, Bullet>();
	SetCollisionPair<Player, Bomb>();
	SetCollisionPair<AIBot, Bomb>();
	SetCollisionPair<Building, Bomb>();
	SetCollisionPair<AIBot, Building>();
}

void LevelTwo::SceneEnd()
{
	delete ui;

	for (int i = 0; i < BuildingsX; ++i)
	{
		for (int j = 0; j < BuildingsZ; j++)
		{
			delete Buildings[i * BuildingsZ + j];
		}
	}

	BotManager::Terminate();
	PlayerManager::Terminate();
	BuildingManager::Terminate();
	BulletFactory::Terminate();
	PlaneBotFactory::Terminate();
	BombFactory::Terminate();
	BuildingManager::Terminate();
}
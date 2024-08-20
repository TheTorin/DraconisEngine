#include "LevelOne.h"
#include "PlayerManager.h"
#include "Player.h"
#include "..//DraconisEngine/Draconis.h"
#include "Bullet.h"
#include "BuildingManager.h"
#include "BulletFactory.h"

void LevelOne::Initialize()
{
	Draconis::setClear(0.4f, 0.4f, 0.8f, 1.0f);
	//SceneManager::getCurrentScene()->setGodCam();

	SetTerrain(TerrainManager::Get("Level1"));

	build1 = new Building();
	build1->Set(Vect(252, 174, 1017));

	build2 = new Building();
	build2->Set(Vect(-717, 174, 1341));

	build3 = new Building();
	build3->Set(Vect(696, 174, 529));

	PlayerManager::SetSpawnPosition(Vect(-813, 174, -921));
	PlayerManager::Initialize();

	gobj1 = new UI();
	gobj1->ToggleBuildingsLeft();

	SetCollisionPair<Player, Bullet>();
	SetCollisionPair<Building, Bullet>();

	SetCollisionTerrain<Player>();
}

void LevelOne::SceneEnd()
{
	delete gobj1;
	delete build1;
	delete build2;
	delete build3;

	BulletFactory::Terminate();
	PlayerManager::Terminate();
	BuildingManager::Terminate();
}
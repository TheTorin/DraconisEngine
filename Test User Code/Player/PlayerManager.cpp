#include "PlayerManager.h"
#include "Player.h"

PlayerManager* PlayerManager::ptrInstance = nullptr;

void PlayerManager::privInit()
{
	currPlayer = new Player();
	currPlayer->SetPos(spawnPosition);
}

Vect PlayerManager::privGetPlayerPos()
{
	return currPlayer->getWorldPos();
}

Matrix PlayerManager::privGetPlayerRot()
{
	return currPlayer->TankBodyRot;
}

int PlayerManager::privGetPlayerHP()
{
	return currPlayer->hp;
}

void PlayerManager::Terminate()
{
	delete Instance().currPlayer;
	delete ptrInstance;
	ptrInstance = nullptr;
}
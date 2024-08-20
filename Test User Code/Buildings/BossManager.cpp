#include "BossManager.h"

BossManager* BossManager::ptrInstance = nullptr;

void BossManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
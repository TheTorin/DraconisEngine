#include "BuildingManager.h"

BuildingManager* BuildingManager::ptrInstance = nullptr;

void BuildingManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
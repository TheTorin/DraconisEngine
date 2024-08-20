#include "TerrainSceneManager.h"
#include "Terrain.h"

TerrainSceneManager::TerrainSceneManager()
{
	pTerrain = nullptr;
}

void TerrainSceneManager::InitializeTerrain()
{
	if (pTerrain == nullptr) return;
	pTerrain->SubmitDrawRegistration();
}

void TerrainSceneManager::UninitializeTerrain()
{
	if (pTerrain == nullptr) return;
	pTerrain->SubmitDrawDeregistration();
}
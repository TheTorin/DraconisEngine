#include "TerrainManager.h"
#include "Terrain.h"
#include "TextureManager.h"

TerrainManager* TerrainManager::ptrInstance = nullptr;

int TerrainManager::privLoad(std::string key, const char* heightmapPath, float sideLen, float maxHeight, float baseY, std::string texture, int uRepeat, int vRepeat)
{
	TerrainMap::iterator it = LoadedTerrain.find(key);
	if (it != LoadedTerrain.end())
	{
		throw std::invalid_argument("Error while loading terrain key: Key " + key + " is already used!");
		return EXIT_FAILURE;
	}
	Terrain* t = new Terrain(heightmapPath, sideLen, maxHeight, baseY, TextureManager::Get(texture), uRepeat, vRepeat);
	LoadedTerrain.insert({ key, t });
	return EXIT_SUCCESS;
}

Terrain* TerrainManager::privGet(const std::string key)
{
	TerrainMap::iterator it = LoadedTerrain.find(key);
	if (it == LoadedTerrain.end())
	{
		throw std::invalid_argument("Error while retrieving terrain: Key " + key + " not found!");
		return NULL;
	}
	return it->second;
}

void TerrainManager::Terminate()
{
	for (TerrainMap::iterator it = Instance().LoadedTerrain.begin(); it != Instance().LoadedTerrain.end(); it++)
	{
		delete it->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}
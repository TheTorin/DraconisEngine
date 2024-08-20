#ifndef _TerrainManager
#define _TerrainManager

#include <map>
#include <string>

class Terrain;
class TerrainManager
{
	friend class TerrainManagerAttorney;
private:
	static TerrainManager* ptrInstance;

	TerrainManager() = default;
	TerrainManager(const TerrainManager&) = delete;
	TerrainManager& operator=(const TerrainManager&) = delete;
	~TerrainManager() = default;

	static TerrainManager& Instance()
	{
		if (!ptrInstance) ptrInstance = new TerrainManager();
		return *ptrInstance;
	}

	using TerrainMap = std::map<std::string, Terrain*>;
	TerrainMap LoadedTerrain;

	int privLoad(std::string key, const char* heightmapPath, float sideLen, float maxHeight, float baseY, std::string texture, int uRepeat, int vRepeat);
	Terrain* privGet(const std::string key);

	static void Terminate();

public:
	static int Load(std::string key, const char* heightmapPath, float sideLen, float maxHeight, float baseY, std::string texture, int uRepeat, int vRepeat)
	{
		return Instance().privLoad(key, heightmapPath, sideLen, maxHeight, baseY, texture, uRepeat, vRepeat);
	};

	static Terrain* Get(const std::string key) { return Instance().privGet(key); };
};

#endif _TerrainManager
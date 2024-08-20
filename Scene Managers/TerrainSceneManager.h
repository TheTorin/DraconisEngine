#ifndef _TerrainSceneManager
#define _TerrainSceneManager

class Terrain;
class TerrainSceneManager
{
private:
	Terrain* pTerrain;

public:
	TerrainSceneManager();
	TerrainSceneManager(const TerrainSceneManager&) = delete;
	TerrainSceneManager& operator=(const TerrainSceneManager&) = delete;
	~TerrainSceneManager() = default;

	void SetTerrain(Terrain* t) { pTerrain = t; };
	Terrain* GetTerrain() { return pTerrain; };

	void UninitializeTerrain();
	void InitializeTerrain();
};

#endif _TerrainSceneManager
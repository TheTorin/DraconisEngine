#ifndef _TerrainRectangle
#define _TerrainRectangle

class Terrain;
class TRectIterator;
class Collidable;
class TerrainRectangle
{
public:
	TerrainRectangle() = delete;
	TerrainRectangle(Collidable* go);
	TerrainRectangle(const TerrainRectangle&);
	TerrainRectangle& operator=(const TerrainRectangle&);
	~TerrainRectangle() = default;

	Terrain* pTerrain;

	int minXIndex;
	int maxXIndex;

	int minZIndex;
	int maxZIndex;

	TRectIterator begin();
	TRectIterator end();
};

#endif _TerrainRectangle
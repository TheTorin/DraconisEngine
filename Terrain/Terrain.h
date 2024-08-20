#ifndef _Terrain
#define _Terrain

#include "AzulCore.h"
#include "GpuVertTypes.h"
#include "Drawable.h"

struct CellAABB
{
	Vect min;
	Vect max;
};

class GameObject;
class Terrain : public Drawable
{
	friend class TerrainAttorney;
private:
	struct Cell
	{
		float minY = 0;
		float maxY = 0;
		int indX = 0;
		int indY = 0;
	};

	Model* terrainMod;
	GraphicsObject_TextureFlat* pTerrain;
	GraphicsObject_WireframeConstantColor* pWireframe;
	Matrix worldMat;
	VertexStride_VUN* pVerts;
	TriangleIndex* tList;
	Cell* cellList;
	CellAABB* cellAABBList;
	Vect* normalList;
	int pixel_width;
	int pixPerSide;
	float startCorner;
	float sideLength;
	float widthPerCell;
	float yOffset;

	int TexelIndex(int i, int j) const;
	int PixelIndex(int i, int j) const;
	int TriIndex(int i, int j) const;
	int CellIndex(int i, int j) const;

	int PosToCellIndex(float x, float z) const;
	int PosToCellIndexCeil(float x, float z) const;

	CellAABB* GetCellFromLoc(int x, int z);

public:
	Terrain() = default;
	Terrain(const char* heightmapPath, float sideLen, float maxHeight, float baseY, Texture* texture, int uRepeat, int vRepeat);
	Terrain(const Terrain&) = delete;
	Terrain& operator=(const Terrain&) = delete;
	~Terrain();

	void Draw(Camera* c);

	void Highlight(float x, float y);
	void HighlightAll(GameObject* m);
	//void Intersect(GameObject* m);

	float GetHeight(float x, float z);
	float GetHeight(GameObject* m);

	Vect GetNormal(float x, float z);
	Vect GetNormal(GameObject* m);

	float GetBaseY() { return yOffset; };

	void Draw() override;
};

#endif _Terrain
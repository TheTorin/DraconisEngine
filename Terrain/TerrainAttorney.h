#ifndef _TerrainAttorney
#define _TerrainAttorney

#include "Terrain.h"

class TerrainAttorney
{
public:
	class IteratorManagement
	{
		friend class TerrainRectangle;
	private:
		static int PosToCellIndex(Terrain* t, float x, float z) { return t->PosToCellIndex(x, z); };
		static int PosToCellIndexCeil(Terrain* t, float x, float z) { return t->PosToCellIndexCeil(x, z); };
		static int CellXIndex(Terrain* t, int i) { return t->cellList[i].indX; };
		static int CellZIndex(Terrain* t, int i) { return t->cellList[i].indY; };
	};
	class ListAccess
	{
		friend class TRectIterator;
	private:
		static CellAABB* GetCellFromLoc(Terrain* t, int x, int z) { return t->GetCellFromLoc(x, z); };
	};
};

#endif _TerrainAttorney
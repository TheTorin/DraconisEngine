#include "TerrainRectangle.h"
#include "Collidable.h"
#include "TerrainAttorney.h"
#include "SceneManager.h"
#include "TRectIterator.h"

TerrainRectangle::TerrainRectangle(Collidable* c)
{
	pTerrain = SceneManager::getCurrentScene()->GetTerrain();

	float rad = c->GetDefaultSphere()->GetRadius();
	Vect center = c->GetDefaultSphere()->GetCenter();
	int minIndex = TerrainAttorney::IteratorManagement::PosToCellIndex(pTerrain, center.X() + rad, center.Z() - rad);
	minXIndex = TerrainAttorney::IteratorManagement::CellXIndex(pTerrain, minIndex);
	minZIndex = TerrainAttorney::IteratorManagement::CellZIndex(pTerrain, minIndex);

	int maxIndex = TerrainAttorney::IteratorManagement::PosToCellIndexCeil(pTerrain, center.X() - rad, center.Z() + rad);
	maxXIndex = TerrainAttorney::IteratorManagement::CellXIndex(pTerrain, maxIndex);
	maxZIndex = TerrainAttorney::IteratorManagement::CellZIndex(pTerrain, maxIndex);
}

TerrainRectangle::TerrainRectangle(const TerrainRectangle& other)
{
	pTerrain = other.pTerrain;
	minXIndex = other.minXIndex;
	maxXIndex = other.maxXIndex;
	minZIndex = other.minZIndex;
	maxZIndex = other.maxZIndex;
}

TerrainRectangle& TerrainRectangle::operator=(const TerrainRectangle& other)
{
	pTerrain = other.pTerrain;
	minXIndex = other.minXIndex;
	maxXIndex = other.maxXIndex;
	minZIndex = other.minZIndex;
	maxZIndex = other.maxZIndex;
	return *this;
}

TRectIterator TerrainRectangle::begin()
{
	return TRectIterator(this, minXIndex, minZIndex);
}

TRectIterator TerrainRectangle::end()
{
	return TRectIterator(this, maxXIndex, maxZIndex);
}
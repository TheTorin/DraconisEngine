#include "TRectIterator.h"
#include "TerrainRectangle.h"
#include "TerrainAttorney.h"

TRectIterator::TRectIterator(TerrainRectangle* parent, int x, int z)
	:pTerRect(parent), xIndex(x), zIndex(z)
{}

TRectIterator::TRectIterator(const TRectIterator & other)
{
	pTerRect = other.pTerRect;
	xIndex = other.xIndex;
	zIndex = other.zIndex;
}

TRectIterator& TRectIterator::operator=(const TRectIterator& other)
{
	pTerRect = other.pTerRect;
	xIndex = other.xIndex;
	zIndex = other.zIndex;
	return *this;
}

TRectIterator& TRectIterator::operator++()
{
	if (xIndex == pTerRect->maxXIndex)
	{
		xIndex = pTerRect->minXIndex;
		++zIndex;
	}
	else ++xIndex;
	return *this;
}

TRectIterator TRectIterator::operator++(int)
{
	int x = xIndex;
	int z = zIndex;
	if (xIndex == pTerRect->maxXIndex)
	{
		xIndex = pTerRect->minXIndex;
		++zIndex;
	}
	else ++xIndex;
	return TRectIterator(pTerRect, x, z);
}

bool TRectIterator::operator==(const TRectIterator& other) const
{
	if (pTerRect == other.pTerRect)
	{
		return (xIndex == other.xIndex && zIndex == other.zIndex);
	}
	else return false;
}

bool TRectIterator::operator!=(const TRectIterator& other) const
{
	if (pTerRect == other.pTerRect)
	{
		return (xIndex != other.xIndex || zIndex != other.zIndex);
	}
	else return true;
}

CellAABB& TRectIterator::operator*()
{
	return *TerrainAttorney::ListAccess::GetCellFromLoc(pTerRect->pTerrain, xIndex, zIndex);
}

CellAABB* TRectIterator::operator->()
{
	return TerrainAttorney::ListAccess::GetCellFromLoc(pTerRect->pTerrain, xIndex, zIndex);
}
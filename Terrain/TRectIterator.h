#ifndef _TRectIterator
#define _TRectIterator

#include <iterator>

struct CellAABB;
class TerrainRectangle;
class TRectIterator
{
private:
	TerrainRectangle* pTerRect;
	int xIndex;
	int zIndex;

public:
	TRectIterator() = delete;
	TRectIterator(TerrainRectangle* parent, int x, int z);
	TRectIterator(const TRectIterator& other);
	TRectIterator& operator=(const TRectIterator& other);
	~TRectIterator() = default;

	TRectIterator& operator++();
	TRectIterator operator++(int);

	bool operator==(const TRectIterator& other) const;
	bool operator!=(const TRectIterator& other) const;

	CellAABB& operator*();
	CellAABB* operator->();
};

#endif _TRectIterator
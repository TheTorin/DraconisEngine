#ifndef _CollisionDispatchTerrain
#define _CollisionDispatchTerrain

#include "CollisionDispatchBase.h"

class Collidable;
template <typename C1, typename C2>
class CollisionDispatchTerrain : public CollisionDispatchBase
{
public:
	CollisionDispatchTerrain() = default;
	CollisionDispatchTerrain(const CollisionDispatchTerrain&) = delete;
	CollisionDispatchTerrain& operator=(const CollisionDispatchTerrain&) = delete;
	~CollisionDispatchTerrain() = default;

	virtual void ProcessCallbacks(Collidable* col1, Collidable* col2) override
	{
		col2;
		C1* pCol1 = static_cast<C1*>(col1);

		pCol1->TerrainCollision();
	};
};

#endif _CollisionDispatchTerrain
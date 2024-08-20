#ifndef _CollisionTestTerrain
#define _CollisionTestTerrain

#include "CollisionTestBase.h"

class CollisionTestTerrain : public CollisionTestBase
{
private:
	CollidableGroup* cGroup;
	CollisionDispatchBase* pDispatch;

public:
	CollisionTestTerrain(CollidableGroup* c, CollisionDispatchBase* d);
	CollisionTestTerrain(const CollisionTestTerrain&) = delete;
	CollisionTestTerrain& operator=(const CollisionTestTerrain&) = delete;
	~CollisionTestTerrain();

	void Execute() override;
};

#endif _CollisionTestTerrain
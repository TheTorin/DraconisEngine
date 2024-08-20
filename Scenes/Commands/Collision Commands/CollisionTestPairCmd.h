#ifndef _CollisionTestPairCmd
#define _CollisionTestPairCmd

#include "CollisionTestBase.h"

class CollisionVolumeBSphere;

class CollisionTestPairCmd : public CollisionTestBase
{
private:
	CollidableGroup* cGroup1;
	CollidableGroup* cGroup2;
	CollisionDispatchBase* pDispatch;

public:
	CollisionTestPairCmd(CollidableGroup* c1, CollidableGroup* c2, CollisionDispatchBase* pBase);
	CollisionTestPairCmd(const CollisionTestPairCmd&) = delete;
	CollisionTestPairCmd& operator=(const CollisionTestPairCmd&) = delete;
	~CollisionTestPairCmd();

	void Execute() override;
};

#endif _CollisionTestPairCmd
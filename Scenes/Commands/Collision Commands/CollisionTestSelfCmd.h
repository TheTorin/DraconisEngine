#ifndef _CollisionTestSelfCmd
#define _CollisionTestSelfCmd

#include "CollisionTestBase.h"

class CollisionVolumeBSphere;

class CollisionTestSelfCmd : public CollisionTestBase
{
private:
	CollidableGroup* cGroup;
	CollisionDispatchBase* pDispatch;

public:
	CollisionTestSelfCmd(CollidableGroup* c, CollisionDispatchBase* pDispatch);
	CollisionTestSelfCmd(const CollisionTestSelfCmd&) = delete;
	CollisionTestSelfCmd& operator=(const CollisionTestSelfCmd&) = delete;
	~CollisionTestSelfCmd();

	void Execute() override;
};

#endif _CollisionTestSelfCmd
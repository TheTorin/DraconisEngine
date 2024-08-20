#ifndef _CollisionTestBase
#define _CollisionTestBase

class CollisionDispatchBase;
class CollidableGroup;
class CollisionTestBase
{
public:
	CollisionTestBase() = default;
	CollisionTestBase(const CollisionTestBase&) = delete;
	CollisionTestBase& operator=(const CollisionTestBase&) = delete;
	virtual ~CollisionTestBase() = default;

	virtual void Execute() = 0;
};

#endif _CollisionTestBase
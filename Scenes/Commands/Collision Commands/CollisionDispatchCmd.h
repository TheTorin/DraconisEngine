#ifndef _CollisionDispatchCmd
#define _CollisionDispatchCmd

#include "CollisionDispatchBase.h"

class Collidable;
template <typename C1, typename C2>
class CollisionDispatchCmd : public CollisionDispatchBase
{
public:
	CollisionDispatchCmd() = default;
	CollisionDispatchCmd(const CollisionDispatchCmd&) = delete;
	CollisionDispatchCmd& operator=(const CollisionDispatchCmd&) = delete;
	~CollisionDispatchCmd() = default;

	virtual void ProcessCallbacks(Collidable* col1, Collidable* col2) override
	{
		C1* pCol1 = static_cast<C1*>(col1);
		C2* pCol2 = static_cast<C2*>(col2);

		pCol1->Collision(pCol2);
		pCol2->Collision(pCol1);
	};
};

#endif _CollisionDispatchCmd
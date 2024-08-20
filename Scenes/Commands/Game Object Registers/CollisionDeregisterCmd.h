#ifndef _CollisionDeregisterCmd
#define _CollisionDeregisterCmd

#include "SceneCommandBase.h"

class Collidable;
class CollisionDeregisterCmd : public SceneCommandBase
{
private:
	Collidable* col;

public:
	CollisionDeregisterCmd(Collidable* c);
	CollisionDeregisterCmd(const CollisionDeregisterCmd&) = delete;
	CollisionDeregisterCmd& operator=(const CollisionDeregisterCmd&) = delete;
	~CollisionDeregisterCmd() = default;

	void Execute() override;
};

#endif _CollisionDeregisterCmd
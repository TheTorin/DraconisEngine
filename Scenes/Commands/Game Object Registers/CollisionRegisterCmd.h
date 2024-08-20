#ifndef _CollisionRegisterCmd
#define _CollisionRegisterCmd

#include "SceneCommandBase.h"

class Collidable;
class CollisionRegisterCmd : public SceneCommandBase
{
private:
	Collidable* col;

public:
	CollisionRegisterCmd(Collidable* c);
	CollisionRegisterCmd(const CollisionRegisterCmd&) = delete;
	CollisionRegisterCmd& operator=(const CollisionRegisterCmd&) = delete;
	~CollisionRegisterCmd() = default;

	void Execute() override;
};

#endif _CollisionRegisterCmd
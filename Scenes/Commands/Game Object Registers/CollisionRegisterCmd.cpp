#include "CollisionRegisterCmd.h"
#include "CollidableAttorney.h"

CollisionRegisterCmd::CollisionRegisterCmd(Collidable* c)
	:col(c)
{

}

void CollisionRegisterCmd::Execute()
{
	CollidableAttorney::Registration::CollisionRegistration(col);
}
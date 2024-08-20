#include "CollisionDeregisterCmd.h"
#include "CollidableAttorney.h"

CollisionDeregisterCmd::CollisionDeregisterCmd(Collidable* c)
	:col(c)
{

}

void CollisionDeregisterCmd::Execute()
{
	CollidableAttorney::Registration::CollisionDeregistration(col);
}
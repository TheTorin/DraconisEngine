#include "CollisionManager.h"
#include "CollidableGroup.h"

CollisionManager::typeID CollisionManager::typeIDNextNum = 0;

void CollisionManager::SetGroupForID(CollisionManager::typeID id)
{
	if ((int)colCollection.size() == id) colCollection.push_back(new CollidableGroup());
}

CollidableGroup* CollisionManager::GetColGroup(CollisionManager::typeID id)
{
	return colCollection[id];
}

void CollisionManager::ProcessCollisions()
{
	CollisionCmds::iterator it;

	for (ColliderCollection::iterator Mit = colCollection.begin(); Mit != colCollection.end(); Mit++)
	{
		(*Mit)->UpdateGroupAABB();
	}

	for (it = colTestCmds.begin(); it != colTestCmds.end(); it++)
	{
		(*it)->Execute();
	}
}

CollisionManager::~CollisionManager()
{
	for (size_t i = 0; i < colCollection.size(); i++)
	{
		delete colCollection[i];
	}

	for (CollisionCmds::iterator it = colTestCmds.begin(); it != colTestCmds.end(); it++)
	{
		delete (*it);
	}
}
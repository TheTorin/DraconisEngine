#include "CollidableGroup.h"
#include "CollisionVolumeAABB.h"
#include "Collidable.h"
#include "CollidableAttorney.h"
#include "Visualizer.h"

CollidableGroup::CollidableGroup()
{
	groupAABB = new CollisionVolumeAABB();
}

void CollidableGroup::Register(Collidable* c, ListRef& ref)
{
	ref = cList.insert(cList.end(), c);
}

void CollidableGroup::Deregister(ListRef ref)
{
	cList.erase(ref);
}

const CollidableGroup::CollideList& CollidableGroup::GetColliderList()
{
	return cList;
}

void CollidableGroup::UpdateGroupAABB()
{
	if (cList.empty()) return;
	groupAABB->ComputeData(CollidableAttorney::Tier::GetDefaultSphere(cList.front()));
	float minX = groupAABB->GetMin().X();
	float maxX = groupAABB->GetMax().X();
	float minY = groupAABB->GetMin().Y();
	float maxY = groupAABB->GetMax().Y();
	float minZ = groupAABB->GetMin().Z();
	float maxZ = groupAABB->GetMax().Z();
	for (ListRef it = cList.begin(); it != cList.end(); it++)
	{
		groupAABB->ComputeData(CollidableAttorney::Tier::GetDefaultSphere(*it));

		if (groupAABB->GetMin().X() < minX) minX = groupAABB->GetMin().X();
		if (groupAABB->GetMax().X() > maxX) maxX = groupAABB->GetMax().X();
		if (groupAABB->GetMin().Y() < minY) minY = groupAABB->GetMin().Y();
		if (groupAABB->GetMax().Y() > maxY) maxY = groupAABB->GetMax().Y();
		if (groupAABB->GetMin().Z() < minZ) minZ = groupAABB->GetMin().Z();
		if (groupAABB->GetMax().Z() > maxZ) maxZ = groupAABB->GetMax().Z();
	}

	groupAABB->SetData(Vect(minX, minY, minZ), Vect(maxX, maxY, maxZ));
}

CollidableGroup::~CollidableGroup()
{
	cList.clear();
	delete groupAABB;
}
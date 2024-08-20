#ifndef _CollidableGroup
#define _CollidableGroup

#include <list>
class Collidable;
class CollisionVolumeAABB;
class CollidableGroup
{
public:
	using CollideList = std::list<Collidable*>;
	using ListRef = CollideList::iterator;

private:
	CollideList cList;
	CollisionVolumeAABB* groupAABB;

public:
	CollidableGroup();
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup& operator=(const CollidableGroup&) = delete;
	~CollidableGroup();

	void Register(Collidable* c, ListRef &ref);
	void Deregister(ListRef ref);
	void UpdateGroupAABB();

	const CollideList& GetColliderList();
	const CollisionVolumeAABB* GetGroupAABB() { return groupAABB; };
};

#endif _CollidableGroup
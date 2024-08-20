#ifndef _CollisionManager
#define _CollisionManager

#include <vector>
#include <list>
#include "AzulCore.h"
#include "CollisionDispatchCmd.h"
#include "CollisionDispatchTerrain.h"
#include "CollisionTestPairCmd.h"
#include "CollisionTestSelfCmd.h"
#include "CollisionTestTerrain.h"

class CollisionManager
{
public:
	using typeID = int;
	static const typeID type_undefined = -1;

private:
	static typeID typeIDNextNum;

	using ColliderCollection = std::vector<CollidableGroup*>;
	ColliderCollection colCollection;

	using CollisionCmds = std::list<CollisionTestBase*>;
	CollisionCmds colTestCmds;

	void SetGroupForID(typeID id);

public:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
	~CollisionManager();

	void ProcessCollisions();

	CollidableGroup* GetColGroup(typeID id);

	///-------------------------------------------------------------------------------------------------
	/// \fn	template <typename C> typeID CollisionManager::GetTypeID()
	///
	/// \brief	Gets type identifier. If a new group, assigns a new identifier.
	///
	/// \tparam	C	Type of the c.
	///
	/// \returns	The type identifier.
	///-------------------------------------------------------------------------------------------------

	template <typename C> typeID GetTypeID()
	{
		static typeID thisID = typeIDNextNum++;

		SetGroupForID(thisID);

		DebugMsg::out("Type ID: %i\n", thisID);
		return thisID;
	}

	///-------------------------------------------------------------------------------------------------
	/// \fn	template <typename C1, typename C2> void CollisionManager::SetCollisionPair()
	///
	/// \brief	Activates collisions between the two given types
	///
	/// \tparam	C1	Type of the c 1.
	/// \tparam	C2	Type of the c 2.
	///-------------------------------------------------------------------------------------------------

	template <typename C1, typename C2> void SetCollisionPair()
	{
		CollidableGroup* group1 = colCollection[GetTypeID<C1>()];
		CollidableGroup* group2 = colCollection[GetTypeID<C2>()];

		CollisionDispatchCmd<C1, C2>* pDispatch = new CollisionDispatchCmd<C1, C2>();

		colTestCmds.push_back(new CollisionTestPairCmd(group1, group2, pDispatch));
	}

	///-------------------------------------------------------------------------------------------------
	/// \fn	template <typename C1> void CollisionManager::SetCollisionSelf()
	///
	/// \brief	Activates collisions between members of the same group
	///
	/// An object will not collide with itself
	/// 
	/// \tparam	C1	Type of the c1.
	///-------------------------------------------------------------------------------------------------

	template <typename C1> void SetCollisionSelf()
	{
		CollidableGroup* group1 = colCollection[GetTypeID<C1>()];

		CollisionDispatchCmd<C1, C1>* pDispatch = new CollisionDispatchCmd<C1, C1>();

		colTestCmds.push_back(new CollisionTestSelfCmd(group1, pDispatch));
	}

	///-------------------------------------------------------------------------------------------------
	/// \fn	template <typename C1> void CollisionManager::SetCollisionTerrain()
	///
	/// \brief	Activates collisions between the group and the terrain
	/// 
	/// \tparam	C1	Type of the c1.
	///-------------------------------------------------------------------------------------------------

	template <typename C1> void SetCollisionTerrain()
	{
		CollidableGroup* group1 = colCollection[GetTypeID<C1>()];

		CollisionDispatchTerrain<C1, C1>* pDispatch = new CollisionDispatchTerrain<C1, C1>();

		colTestCmds.push_back(new CollisionTestTerrain(group1, pDispatch));
	}
};

#endif _CollisionManager
#include "CollisionTestTerrain.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "Collidable.h"
#include "TRectIterator.h"
#include "TerrainRectangle.h"
#include "Terrain.h"
#include "CollisionVolumeAABB.h"
#include "DragonMath.h"
#include "Color.h"
#include "Visualizer.h"

CollisionTestTerrain::CollisionTestTerrain(CollidableGroup* c, CollisionDispatchBase* p)
	:cGroup(c), pDispatch(p)
{}

void CollisionTestTerrain::Execute()
{
	const CollidableGroup::CollideList& group = cGroup->GetColliderList();

	CollidableGroup::CollideList::const_iterator it;
	CollisionVolumeAABB testCell;

	for (it = group.begin(); it != group.end(); ++it)
	{
		TerrainRectangle cells = TerrainRectangle(*it);

		for (TRectIterator itCell = cells.begin(); itCell != cells.end(); ++itCell)
		{
			testCell.SetData(itCell->min, itCell->max);

			Visualizer::showBSphere(*(*it)->GetDefaultSphere());
			if (DragonMath::Intersect(*(*it)->GetDefaultSphere(), testCell))
			{
				Visualizer::showCollisionVolume(*(*it)->GetCollisionVolume());
				if (DragonMath::Intersect(*(*it)->GetCollisionVolume(), testCell))
				{
					Visualizer::showAABB(testCell, Color::Red);

					pDispatch->ProcessCallbacks(*it, *it);
				}
				else Visualizer::showAABB(testCell, Color::Yellow);
			}
			else Visualizer::showAABB(testCell, Color::Green);
		}
	}
}

CollisionTestTerrain::~CollisionTestTerrain()
{
	delete pDispatch;
}
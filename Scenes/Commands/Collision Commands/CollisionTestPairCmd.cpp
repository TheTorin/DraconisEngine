#include "CollisionTestPairCmd.h"
#include "CollidableGroup.h"
#include "CollisionVolumeAABB.h"
#include "CollidableAttorney.h"
#include "CollisionDispatchBase.h"
#include "Collidable.h"
#include "DragonMath.h"
#include "Color.h"
#include "Visualizer.h"

CollisionTestPairCmd::CollisionTestPairCmd(CollidableGroup* c1, CollidableGroup* c2, CollisionDispatchBase* pBase)
	:cGroup1(c1), cGroup2(c2), pDispatch(pBase)
{

}

void CollisionTestPairCmd::Execute()
{
	const CollisionVolumeAABB* aabb1 = cGroup1->GetGroupAABB();
	const CollisionVolumeAABB* aabb2 = cGroup2->GetGroupAABB();

	//Visualizer::showCollisionVolume(*aabb1, Color::Green);
	//Visualizer::showCollisionVolume(*aabb2, Color::Green);

	//Test 1 - AABB vs AABB
	if (DragonMath::Intersect(*aabb1, *aabb2))
	{
		const CollidableGroup::CollideList& group1 = cGroup1->GetColliderList();
		CollidableGroup::CollideList::const_iterator it1;

		for (it1 = group1.begin(); it1 != group1.end(); it1++)
		{
			const CollisionVolumeBSphere* s1 = CollidableAttorney::Tier::GetDefaultSphere(*it1);

			//Test 2 - default bSphere vs AABB
			if (DragonMath::Intersect(*s1, *aabb2))
			{
				//Visualizer::showCollisionVolume(*s1, Color::Yellow);

				const CollidableGroup::CollideList& group2 = cGroup2->GetColliderList();
				CollidableGroup::CollideList::const_iterator it2;

				for (it2 = group2.begin(); it2 != group2.end(); it2++)
				{
					const CollisionVolumeBSphere* s2 = CollidableAttorney::Tier::GetDefaultSphere(*it2);

					//Test 3 - default bSphere vs default bSphere
					if (DragonMath::Intersect(*s1, *s2))
					{
						const CollisionVolume* cv1 = (*it1)->GetCollisionVolume();
						const CollisionVolume* cv2 = (*it2)->GetCollisionVolume();

						//Test 4 - chosen volume vs chosen volume
						if (DragonMath::Intersect(*cv1, *cv2))
						{
							pDispatch->ProcessCallbacks(*it1, *it2);

							//Visualizer::showCollisionVolume(*cv1, Color::Red);
							//Visualizer::showCollisionVolume(*cv2, Color::Red);
						}
						else
						{
							//Visualizer::showCollisionVolume(*cv1, Color::Blue);
							//Visualizer::showCollisionVolume(*cv2, Color::Blue);
						}
					}
				}
			}
			else
			{
				//Visualizer::showCollisionVolume(*s1, Color::LightGray);
			}
		}
	}
}

CollisionTestPairCmd::~CollisionTestPairCmd()
{
	delete pDispatch;
}
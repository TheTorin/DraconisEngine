#include "CollisionTestSelfCmd.h"
#include "CollidableGroup.h"
#include "CollidableAttorney.h"
#include "CollisionDispatchBase.h"
#include "DragonMath.h"
#include "Color.h"
#include "Visualizer.h"

CollisionTestSelfCmd::CollisionTestSelfCmd(CollidableGroup* c, CollisionDispatchBase* pBase)
	:cGroup(c), pDispatch(pBase)
{

}

void CollisionTestSelfCmd::Execute()
{
	const CollidableGroup::CollideList& group = cGroup->GetColliderList();
	
	CollidableGroup::CollideList::const_iterator outer;
	CollidableGroup::CollideList::const_iterator inner;

	for (outer = group.begin(); outer != group.end(); outer++)
	{
		const CollisionVolumeBSphere* s1 = CollidableAttorney::Tier::GetDefaultSphere(*outer);

		for (inner = std::next(outer); inner != group.end(); inner++)
		{
			const CollisionVolumeBSphere* s2 = CollidableAttorney::Tier::GetDefaultSphere(*inner);

			if (DragonMath::Intersect(*s1, *s2))
			{
				const CollisionVolume* cv1 = (*outer)->GetCollisionVolume();
				const CollisionVolume* cv2 = (*inner)->GetCollisionVolume();
				
				if (DragonMath::Intersect(*cv1, *cv2))
				{
					pDispatch->ProcessCallbacks(*outer, *inner);

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
}

CollisionTestSelfCmd::~CollisionTestSelfCmd()
{
	delete pDispatch;
}
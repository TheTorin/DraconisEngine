#ifndef _DragonMath
#define _DragonMath

#include "AzulCore.h"

class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolumeBox;

namespace DragonMath
{
	float ProjectionLength(Vect projectThis, Vect ontoThis);
	float MaxProjection(const CollisionVolumeBox& ob1, Vect axis);
	Vect Projection(Vect projectThis, Vect ontoThis);

	float Clamp(float value, float min, float max);
	Vect Clamp(Vect value, Vect min, Vect max);

	bool Intersect(const CollisionVolumeBSphere& bs1, const Vect point);
	bool Intersect(const CollisionVolume& col1, const CollisionVolume& col2);
	bool Intersect(const CollisionVolumeBSphere& bs1, const CollisionVolumeBSphere& bs2);
	bool Intersect(const CollisionVolumeBSphere& bs1, const CollisionVolumeAABB& ab1);
	bool Intersect(const CollisionVolumeAABB& ab1, const CollisionVolumeAABB& ab2);
	bool Intersect(const CollisionVolumeBSphere& bs1, const CollisionVolumeOBB& ob1);
	bool Intersect(const CollisionVolumeAABB& ab1, const CollisionVolumeOBB& ob1);
	bool Intersect(const CollisionVolumeOBB& ob1, const CollisionVolumeOBB& ob2);
};

#endif _DragonMath
#include "CollisionVolumeOBB.h"
#include "Visualizer.h"
#include "DragonMath.h"

void CollisionVolumeOBB::ComputeData(Model* m, const Matrix& mat)
{
	cornerMin = m->getMinAABB();
	cornerMax = m->getMaxAABB();

	halfDiagonal = 0.5f * (m->getMaxAABB() - m->getMinAABB());
	world = mat;
	worldCenter = (m->getMinAABB() + halfDiagonal) * mat;
	scaleSquared = (Vect(0, 0, 1, 0) * mat).magSqr();
}

void CollisionVolumeOBB::DebugView(const Vect& col) const
{
	Visualizer::showOBB(*this, col);
}

bool CollisionVolumeOBB::IntersectRequest(const CollisionVolume& other) const
{
	return other.IntersectCompute(*this);
}

bool CollisionVolumeOBB::IntersectCompute(const CollisionVolumeBSphere& other) const
{
	return DragonMath::Intersect(other, *this);
}

bool CollisionVolumeOBB::IntersectCompute(const CollisionVolumeAABB& other) const
{
	return DragonMath::Intersect(other, *this);
}

bool CollisionVolumeOBB::IntersectCompute(const CollisionVolumeOBB& other) const
{
	return DragonMath::Intersect(*this, other);
}
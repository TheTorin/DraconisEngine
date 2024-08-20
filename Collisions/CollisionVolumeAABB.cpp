#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "DragonMath.h"
#include "Visualizer.h"

void CollisionVolumeAABB::ComputeData(Model* m, const Matrix& mat)
{
	int numPoints = m->getVectNum();
	Vect* points = m->getVectList();

	Vect first = points[0] * mat;

	float minX = first.X();
	float minY = first.Y();
	float minZ = first.Z();
	
	float maxX = first.X();
	float maxY = first.Y();
	float maxZ = first.Z();

	for (int i = 0; i < numPoints; i++)
	{
		Vect currPoint = points[i] * mat;

		if (currPoint.X() < minX) minX = currPoint.X();
		else if (currPoint.X() > maxX) maxX = currPoint.X();

		if (currPoint.Y() < minY) minY = currPoint.Y();
		else if (currPoint.Y() > maxY) maxY = currPoint.Y();

		if (currPoint.Z() < minZ) minZ = currPoint.Z();
		else if (currPoint.Z() > maxZ) maxZ = currPoint.Z();
	}

	cornerMin = Vect(minX, minY, minZ);
	cornerMax = Vect(maxX, maxY, maxZ);
	halfDiagonal = 0.5f * (m->getMaxAABB() - m->getMinAABB());
	world = mat;
	worldCenter = (m->getMinAABB() + halfDiagonal) * mat;
	scaleSquared = (Vect(0, 0, 1) * mat).magSqr();
}

void CollisionVolumeAABB::ComputeData(CollisionVolumeBSphere* bs)
{
	float radius = bs->GetRadius();
	Vect rad = Vect(radius, radius, radius);
	cornerMin = bs->GetCenter() - rad;
	cornerMax = bs->GetCenter() + rad;
	world = Matrix(TRANS, bs->GetCenter());
	Vect localMin = cornerMin * world.getInv();
	Vect localMax = cornerMax * world.getInv();
	halfDiagonal = 0.5f * (localMax - localMin);
	worldCenter = bs->GetCenter();
	scaleSquared = 1;
}

void CollisionVolumeAABB::SetData(Vect min, Vect max)
{
	cornerMin = min;
	cornerMax = max;
	worldCenter = cornerMin + ((cornerMax - cornerMin) * 0.5f);
	world = Matrix(TRANS, worldCenter);
	Vect localMin = cornerMin * world.getInv();
	Vect localMax = cornerMax * world.getInv();
	halfDiagonal = 0.5f * (localMax - localMin);
	scaleSquared = 1;
}

void CollisionVolumeAABB::DebugView(const Vect& col) const
{
	Visualizer::showAABB(*this, col);
}

bool CollisionVolumeAABB::IntersectRequest(const CollisionVolume& other) const
{
	return other.IntersectCompute(*this);
}

bool CollisionVolumeAABB::IntersectCompute(const CollisionVolumeBSphere& other) const
{
	return DragonMath::Intersect(other, *this);
}

bool CollisionVolumeAABB::IntersectCompute(const CollisionVolumeAABB& other) const
{
	return DragonMath::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectCompute(const CollisionVolumeOBB& other) const
{
	return DragonMath::Intersect(*this, other);
}
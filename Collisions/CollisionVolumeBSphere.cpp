#include "CollisionVolumeBSphere.h"
#include "DragonMath.h"
#include "Visualizer.h"

void CollisionVolumeBSphere::ComputeData(Model* mod, const Matrix& mat)
{
	Vect c = mod->getCenter();

	Vect toUse = mod->getRadius() * Vect(1, 1, 1);

	Matrix correctPos = Matrix(SCALE, toUse) * Matrix(TRANS, c) * mat;

	center = correctPos.get(MatrixRowType::ROW_3);

	radius = correctPos.get(MatrixRowType::ROW_0).mag();

	/*	Vect vBSSize = model->radius * Vect(1, 1, 1);
	Vect vBSPos = model->center;

	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix worldBS = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos) * world;*/
}

const Vect& CollisionVolumeBSphere::GetCenter() const
{
	return center;
}

float CollisionVolumeBSphere::GetRadius() const
{
	return radius;
}

void CollisionVolumeBSphere::DebugView(const Vect& col) const
{
	Visualizer::showBSphere(*this, col);
}

bool CollisionVolumeBSphere::IntersectRequest(const CollisionVolume& other) const
{
	return other.IntersectCompute(*this);
}

bool CollisionVolumeBSphere::IntersectCompute(const CollisionVolumeBSphere& other) const
{
	return DragonMath::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectCompute(const CollisionVolumeAABB& other) const
{
	return DragonMath::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectCompute(const CollisionVolumeOBB& other) const
{
	return DragonMath::Intersect(*this, other);
}
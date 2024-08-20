#ifndef _CollisionVolumeBox
#define _CollisionVolumeBox

#include "CollisionVolume.h"

class CollisionVolumeBox : public CollisionVolume
{
protected:
	Matrix world;
	Vect cornerMin;
	Vect cornerMax;
	Vect halfDiagonal;
	Vect worldCenter;
	float scaleSquared;

public:
	CollisionVolumeBox() = default;
	CollisionVolumeBox(const CollisionVolumeBox&) = delete;
	CollisionVolumeBox& operator=(const CollisionVolumeBox&) = delete;
	~CollisionVolumeBox() = default;

	virtual void ComputeData(Model* m, const Matrix& mat) = 0;

	virtual void DebugView(const Vect& col) const = 0;

	virtual bool IntersectRequest(const CollisionVolume& other) const = 0;

	virtual bool IntersectCompute(const CollisionVolumeBSphere& other) const = 0;

	virtual bool IntersectCompute(const CollisionVolumeAABB& other) const = 0;

	virtual bool IntersectCompute(const CollisionVolumeOBB& other) const = 0;

	Vect GetMin() const { return cornerMin; };

	Vect GetMax() const { return cornerMax; };

	Vect GetHalfDiagonal() const { return halfDiagonal; };

	Vect GetWorldCenter() const { return worldCenter; };

	float GetScaleSquared() const { return scaleSquared; };

	Matrix GetWorld() const { return world; };
};

#endif _CollisionVolumeBox
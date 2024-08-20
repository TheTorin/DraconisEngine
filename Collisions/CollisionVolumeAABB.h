#ifndef _CollisionVolumeAABB
#define _CollisionVolumeAABB

#include "CollisionVolumeBox.h"

class CollisionVolumeBSphere;
class CollisionVolumeAABB : public CollisionVolumeBox
{
private:

public:
	CollisionVolumeAABB() = default;
	CollisionVolumeAABB(const CollisionVolumeAABB&) = delete;
	CollisionVolumeAABB& operator=(const CollisionVolumeAABB&) = delete;
	~CollisionVolumeAABB() = default;

	void ComputeData(Model* m, const Matrix& mat) override;

	void ComputeData(CollisionVolumeBSphere* bs);

	void SetData(Vect min, Vect max);

	void DebugView(const Vect& col) const override;

	bool IntersectRequest(const CollisionVolume& other) const override;

	bool IntersectCompute(const CollisionVolumeBSphere& other) const override;

	bool IntersectCompute(const CollisionVolumeAABB& other) const override;

	bool IntersectCompute(const CollisionVolumeOBB& other) const override;
};

#endif _CollisionVolumeAABB
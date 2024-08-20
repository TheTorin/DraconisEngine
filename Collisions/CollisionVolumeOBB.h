#ifndef _CollisionVolumeOBB
#define _CollisionVolumeOBB

#include "CollisionVolumeBox.h"

class CollisionVolumeOBB : public CollisionVolumeBox
{
private:

public:
	CollisionVolumeOBB() = default;
	CollisionVolumeOBB(const CollisionVolumeOBB&) = delete;
	CollisionVolumeOBB& operator=(const CollisionVolumeOBB&) = delete;
	~CollisionVolumeOBB() = default;

	void ComputeData(Model* m, const Matrix& mat) override;

	void DebugView(const Vect& col) const override;

	bool IntersectRequest(const CollisionVolume& other) const override;

	bool IntersectCompute(const CollisionVolumeBSphere& other) const override;

	bool IntersectCompute(const CollisionVolumeAABB& other) const override;

	bool IntersectCompute(const CollisionVolumeOBB& other) const override;
};

#endif _CollisionVolumeOBB
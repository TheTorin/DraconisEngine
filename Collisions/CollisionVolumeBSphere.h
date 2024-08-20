#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "CollisionVolume.h"

class CollisionVolumeBSphere : public CollisionVolume
{
private:
	Vect center;
	float radius;

public:
	CollisionVolumeBSphere() = default;
	CollisionVolumeBSphere(const CollisionVolumeBSphere&) = delete;
	CollisionVolumeBSphere& operator=(const CollisionVolumeBSphere&) = delete;
	~CollisionVolumeBSphere() = default;

	///-------------------------------------------------------------------------------------------------
	/// \fn	void CollisionVolumeBSphere::ComputeData(Model* mod, const Matrix& mat) override;
	///
	/// \brief	Updates data of the bounding sphere
	///
	/// \param [in,out]	mod	If non-null, the model the bSphere belongs to.
	/// \param 		   	mat	The world matrix of the model.
	///-------------------------------------------------------------------------------------------------

	void ComputeData(Model* mod, const Matrix& mat) override;

	///---------------------------------
	///	\fn	void CollisionVolumeBSphere::DebugView(const Vect& col) override;
	///
	///	\brief	Calls on the visualizer to draw this collision volume
	///
	///	\param	col	The color for the visualizer to use
	///---------------------------------

	void DebugView(const Vect& col) const override;

	///-----------------------------
	///	\fn bool CollisionVolumeBSphere::IntersectRequest(const CollisionVolume& other) const override;
	///
	///	\brief	Part of the visitor pattern. Calls IntersectCompute on other
	///
	///	\param	other	The CollisionVolume to test for intersection against
	///-----------------------------

	bool IntersectRequest(const CollisionVolume& other) const override;

	///-----------------------------
	///	\fn	bool CollisionVolumeBSphere::IntersectCompute(const CollisionVolumeBSphere& other) const override;
	///
	///	\brief	Part of the visitor pattern. Routes the request to DragonMath now that we know the volume base types.
	///
	///	\param	other	The CollisionVolumeBSphere to test against
	///-----------------------------

	bool IntersectCompute(const CollisionVolumeBSphere& other) const override;

	bool IntersectCompute(const CollisionVolumeAABB& other) const override;

	bool IntersectCompute(const CollisionVolumeOBB& other) const override;

	///-------------------------------------------------------------------------------------------------
	/// \fn	float CollisionVolumeBSphere::GetRadius() const;
	///
	/// \brief	Gets the radius of the bounding sphere
	///
	/// \returns	The radius.
	///-------------------------------------------------------------------------------------------------

	float GetRadius() const;

	///-------------------------------------------------------------------------------------------------
	/// \fn	const Vect& CollisionVolumeBSphere::GetCenter() const;
	///
	/// \brief	Gets the center of the bounding sphere
	///
	/// \returns	The center.
	///-------------------------------------------------------------------------------------------------

	const Vect& GetCenter() const;
};

#endif _CollisionVolumeBSphere
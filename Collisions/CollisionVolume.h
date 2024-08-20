#ifndef _CollisionVolume
#define _CollisionVolume

#include "AzulCore.h"

class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolume
{
public:
	CollisionVolume() = default;
	CollisionVolume(const CollisionVolume&) = delete;
	CollisionVolume& operator=(const CollisionVolume&) = delete;
	virtual ~CollisionVolume() = default;

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void CollisionVolume::ComputeData(Model* m, const Matrix& mat) = 0;
	///
	/// \brief	Calculates the data of the CollisionVolume
	///
	/// \param [in,out]	m  	If non-null, a Model to process.
	/// \param 		   	mat	The matrix of the Model.
	///-------------------------------------------------------------------------------------------------

	virtual void ComputeData(Model* m, const Matrix& mat) = 0;

	///-----------------------------
	/// \fn virtual void CollisionVolume::DebugView(const Vect& col) = 0;
	///
	/// \brief Used by the visualizer. Makes the model call the correct function in order to display itself
	///
	///	\param	col	The color the visualizer will use when drawing the collision volume
	///-----------------------------

	virtual void DebugView(const Vect& col) const = 0;

	///-----------------------------
	/// \fn virtual bool IntersectRequest(const CollisionVolume& other) const = 0;
	///
	///	\brief	Part of a visitor pattern. Gets routed to base class call
	///
	///	\param other	The CollisionVolume to test an intersection against
	///-----------------------------

	virtual bool IntersectRequest(const CollisionVolume& other) const = 0;

	///-----------------------------
	///	\fn	virtual bool IntersectCompute(const CollisionVolumeBSphere& other) const = 0;
	///
	/// \brief Part of a visitor pattern. Gets routed to base class call
	///
	///	\param	other	The CollisionVolumeBSphere to test an intersection against
	///-----------------------------

	virtual bool IntersectCompute(const CollisionVolumeBSphere& other) const = 0;

	virtual bool IntersectCompute(const CollisionVolumeAABB& other) const = 0;

	virtual bool IntersectCompute(const CollisionVolumeOBB& other) const = 0;
};

#endif _CollisionVolume
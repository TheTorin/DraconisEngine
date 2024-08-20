#ifndef _Collidable
#define _Collidable

#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "SceneBaseAttorney.h"
#include "RegistrationStates.h"
#include "CollisionVolumeBSphere.h"

enum VolumeType
{
	BSPHERE,
	AABB,
	OBB
};

class CollisionRegisterCmd;
class CollisionDeregisterCmd;

class Collidable
{
	friend class CollidableAttorney;
private:
	CollisionManager::typeID myID = CollisionManager::type_undefined;

	RegistrationStates regState;
	CollisionRegisterCmd* pRegister;
	CollisionDeregisterCmd* pDeregister;
	CollidableGroup::ListRef pDeleteRef;

	CollisionVolumeBSphere* defaultSphere;
	CollisionVolume* colVolume;
	Model* pModel;

	void CollisionRegistration();
	void CollisionDeregistration();

public:
	Collidable();
	Collidable(const Collidable&) = delete;
	Collidable& operator=(const Collidable&) = delete;
	virtual ~Collidable();

	///-------------------------------------------------------------------------------------------------
	/// \fn	template <typename C> void Collidable::SetCollidableGroup()
	///
	/// \brief	Sets collidable group for this object to belong to. Only needs to be called once.
	///
	/// \tparam	C	The name of the group the object will be part of
	///-------------------------------------------------------------------------------------------------

	template <typename C> void SetCollidableGroup()
	{
		myID = SceneBaseAttorney::CollisionRegistration::GetColManager(SceneManager::getCurrentScene())->GetTypeID<C>();
	}

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Collidable::SubmitCollisionRegistration();
	/// \ingroup (DE)REGISTRATION_EVENTS
	///
	/// \brief	Submit collision registration for this object
	/// 		
	/// \note	In order to have collision work, the object must be given a collidable group with SetCollidableGroup<C>
	/// 		and collision must be set within the current scene with SetCollisionPair<C, D> or with SetCollisionSelf<C>
	/// 		
	/// \par Processing Collisions
	/// 
	/// Collision events are processed by each object through the function:
	///		\code
	///			virtual void Collision(<otherGroup>* other)
	///		\endcode
	///	
	///	If this function does not exist, nothing will happen
	///
	///-------------------------------------------------------------------------------------------------

	void SubmitCollisionRegistration();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Collidable::SubmitCollisionDeregistration();
	/// \ingroup (DE)REGISTRATION_EVENTS
	///
	/// \brief	Submit collision deregistration for this object
	///-------------------------------------------------------------------------------------------------

	void SubmitCollisionDeregistration();

	///-------------------------------------------------------------------------------------------------
	/// \fn	const CollisionVolume* Collidable::GetCollisionVolume();
	///
	/// \brief	Gets the collision volume used during collision for this object
	///
	/// \returns	The CollisionVolume used by the object.
	///-------------------------------------------------------------------------------------------------

	const CollisionVolume* GetCollisionVolume();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Collidable::SetColliderModel(Model* m);
	///
	/// \brief	Sets collider model for this object. Often done with (objName)->getModel()
	///
	/// \param [in,out]	m	If non-null, a Model to process.
	///-------------------------------------------------------------------------------------------------

	void SetColliderModel(Model* m, VolumeType vol);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Collidable::UpdateCollisionData(const Matrix& mat);
	///
	/// \brief	Updates the collision data described by the given Matrix. Should be called whenever the object moves.
	///
	/// \param 	mat	The world matrix of the object.
	///-------------------------------------------------------------------------------------------------

	void UpdateCollisionData(const Matrix& mat);

	CollisionVolumeBSphere* GetDefaultSphere() { return defaultSphere; };
};

#endif _Collidable
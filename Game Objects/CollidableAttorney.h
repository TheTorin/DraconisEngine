#ifndef _CollidableAttorney
#define _CollidableAttorney

#include "Collidable.h"

class CollidableAttorney
{
public:
	class Registration
	{
		friend class CollisionRegisterCmd;
		friend class CollisionDeregisterCmd;
	private:
		static void CollisionRegistration(Collidable* c) { c->CollisionRegistration(); };
		static void CollisionDeregistration(Collidable* c) { c->CollisionDeregistration(); };
	};
	class Tier
	{
		friend class CollidableGroup;
		friend class CollisionTestPairCmd;
		friend class CollisionTestSelfCmd;
	private:
		static CollisionVolumeBSphere* GetDefaultSphere(Collidable* c) { return c->GetDefaultSphere(); };
	};
};

#endif _CollidableAttorney
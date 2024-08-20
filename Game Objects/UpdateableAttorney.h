#ifndef _UpdateableAttorney
#define _UpdateableAttorney

#include "Updateable.h"

class UpdateableAttorney
{
public:
	class UpdateLoop
	{
		friend class UpdateableManager;
	private:
		static void Update(Updateable* up) { up->Update(); };
	};

	class Registration
	{
		friend class UpdateRegisterCmd;
		friend class UpdateDeregisterCmd;
	private:
		static void SceneRegistration(Updateable* up) { up->UpdateRegistration(); };
		static void SceneDeregistration(Updateable* up) { up->UpdateDeregistration(); };
	};
};

#endif _UpdateableAttorney
#include "UpdateRegisterCmd.h"
#include "UpdateableAttorney.h"

UpdateRegisterCmd::UpdateRegisterCmd(Updateable* up)
	: ptrUp(up)
{
}

void UpdateRegisterCmd::Execute()
{
	UpdateableAttorney::Registration::SceneRegistration(ptrUp);
}
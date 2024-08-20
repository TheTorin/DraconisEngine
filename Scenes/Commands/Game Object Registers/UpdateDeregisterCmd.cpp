#include "UpdateDeregisterCmd.h"
#include "UpdateableAttorney.h"

UpdateDeregisterCmd::UpdateDeregisterCmd(Updateable* up)
	:ptrUp(up)
{

}

void UpdateDeregisterCmd::Execute()
{
	UpdateableAttorney::Registration::SceneDeregistration(ptrUp);
}
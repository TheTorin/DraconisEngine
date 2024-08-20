#include "InputableDeregisterCmd.h"
#include "InputableAttorney.h"

InputableDeregisterCmd::InputableDeregisterCmd(Inputable* in, AZUL_KEY k, EventType::EVENT_TYPE ev)
	:input(in), key(k), event(ev)
{

}

void InputableDeregisterCmd::Execute()
{
	InputableAttorney::Registration::InputDeregistration(input, key, event);
}
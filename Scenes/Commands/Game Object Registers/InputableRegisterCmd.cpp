#include "InputableRegisterCmd.h"
#include "InputableAttorney.h"

InputableRegisterCmd::InputableRegisterCmd(Inputable* in, AZUL_KEY k, EventType::EVENT_TYPE ev)
	:input(in), key(k), event(ev)
{

}

void InputableRegisterCmd::Execute()
{
	InputableAttorney::Registration::InputRegistration(input, key, event);
}
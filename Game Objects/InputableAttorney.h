#ifndef _InputableAttorney
#define _InputableAttorney

#include "Inputable.h"
#include "EventTypeEnum.h"

class InputableAttorney
{
public:
	class InputLoop
	{
		friend class SingleKeyEventManager;
	private:
		static void KeyPressed(Inputable* input, AZUL_KEY k) { input->KeyPressed(k); };
		static void KeyHeldDown(Inputable* input, AZUL_KEY k) { input->KeyHeldDown(k); };
		static void KeyReleased(Inputable* input, AZUL_KEY k) { input->KeyReleased(k); };
		static void KeyHeldUp(Inputable* input, AZUL_KEY k) { input->KeyHeldUp(k); };
	};
	class Registration
	{
		friend class InputableRegisterCmd;
		friend class InputableDeregisterCmd;
	private:
		static void InputRegistration(Inputable* input, AZUL_KEY k, EventType::EVENT_TYPE ev) { input->InputRegistration(k, ev); };
		static void InputDeregistration(Inputable* input, AZUL_KEY k, EventType::EVENT_TYPE ev) { input->InputDeregistration(k, ev); };
	};
};

#endif _InputableAttorney
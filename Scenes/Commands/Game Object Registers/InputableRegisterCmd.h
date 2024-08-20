#ifndef _InputableRegisterCmd
#define _InputableRegisterCmd

#include "SceneCommandBase.h"
#include "EventTypeEnum.h"
#include "AzulCore.h"

class Inputable;
class InputableRegisterCmd : public SceneCommandBase
{
private:
	Inputable* input;
	AZUL_KEY key;
	EventType::EVENT_TYPE event;

public:
	InputableRegisterCmd(Inputable* in, AZUL_KEY k, EventType::EVENT_TYPE ev);
	InputableRegisterCmd(const InputableRegisterCmd&) = delete;
	InputableRegisterCmd& operator=(const InputableRegisterCmd&) = delete;
	~InputableRegisterCmd() = default;

	void Execute() override;
};

#endif _InputableRegisterCmd
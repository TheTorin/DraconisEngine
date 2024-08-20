#ifndef _InputableDeregisterCmd
#define _InputableDeregisterCmd

#include "SceneCommandBase.h"
#include "EventTypeEnum.h"
#include "AzulCore.h"

class Inputable;
class InputableDeregisterCmd : public SceneCommandBase
{
private:
	Inputable* input;
	AZUL_KEY key;
	EventType::EVENT_TYPE event;

public:
	InputableDeregisterCmd(Inputable* in, AZUL_KEY k, EventType::EVENT_TYPE ev);
	InputableDeregisterCmd(const InputableDeregisterCmd&) = delete;
	InputableDeregisterCmd& operator=(const InputableDeregisterCmd&) = delete;
	~InputableDeregisterCmd() = default;

	void Execute() override;
};

#endif _InputableDeregisterCmd
#include "SceneBroker.h"
#include "SceneCommandBase.h"

void SceneBroker::addCommand(SceneCommandBase* cmd)
{
	cmdQueue.push(cmd);
}

void SceneBroker::executeCommands()
{
	while (!cmdQueue.empty())
	{
		cmdQueue.front()->Execute();
		cmdQueue.pop();
	}
}
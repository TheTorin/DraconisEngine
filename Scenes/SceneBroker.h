#ifndef _SceneBroker
#define _SceneBroker

#include <queue>

class SceneCommandBase;

class SceneBroker
{
private:
	using CommandQueue = std::queue<SceneCommandBase*>;
	CommandQueue cmdQueue;

public:
	SceneBroker() = default;
	SceneBroker(const SceneBroker&) = delete;
	SceneBroker& operator=(const SceneBroker&) = delete;
	~SceneBroker() = default;

	void addCommand(SceneCommandBase* cmd);
	void executeCommands();
};

#endif _SceneBroker
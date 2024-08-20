#ifndef _CommandBase
#define _CommandBase

class SceneCommandBase
{
public:
	SceneCommandBase() = default;
	SceneCommandBase(const SceneCommandBase&) = delete;
	SceneCommandBase& operator=(const SceneCommandBase) = delete;
	~SceneCommandBase() = default;

	virtual void Execute() {};
};

#endif _CommandBase
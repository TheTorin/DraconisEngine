#ifndef _SceneChangeCmdBase
#define _SceneChangeCmdBase

class Scene;
class SceneChangeBase
{
public:
	SceneChangeBase() = default;
	SceneChangeBase(const SceneChangeBase&) = delete;
	SceneChangeBase& operator=(const SceneChangeBase&) = delete;
	~SceneChangeBase() = default;

	virtual void Execute() {};
	virtual Scene* getHeldScene() { return nullptr; };
};

#endif _SceneChangeCmdBase
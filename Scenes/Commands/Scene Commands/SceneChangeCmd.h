#ifndef _SceneChangeCmd
#define _SceneChangeCmd

#include "SceneChangeCmdBase.h"

class SceneChangeCmd : public SceneChangeBase
{
private:
	Scene* s;

public:
	SceneChangeCmd() = default;
	SceneChangeCmd(const SceneChangeCmd&) = delete;
	SceneChangeCmd& operator=(const SceneChangeCmd&) = delete;
	~SceneChangeCmd() = default;

	void Execute() override;
	Scene* getHeldScene() override;
	void changeHeldScene(Scene* ns);
};

#endif _SceneChangeCmd
#ifndef _GameObjectEnterCmd
#define _GameObjectEnterCmd

#include "SceneCommandBase.h"

class GameObject;
class GameObjectEnterCmd : public SceneCommandBase
{
private:
	GameObject* gameObj;

public:
	GameObjectEnterCmd(GameObject* go);
	GameObjectEnterCmd(const GameObjectEnterCmd&) = delete;
	GameObjectEnterCmd& operator=(const GameObjectEnterCmd&) = delete;
	~GameObjectEnterCmd() = default;

	void Execute() override;
};

#endif _GameObjectEnterCmd
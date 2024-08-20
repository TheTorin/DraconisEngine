#ifndef _GameObjectExitCmd
#define _GameObjectExitCmd

#include "SceneCommandBase.h"

class GameObject;
class GameObjectExitCmd : public SceneCommandBase
{
private:
	GameObject* gameObj;

public:
	GameObjectExitCmd(GameObject* go);
	GameObjectExitCmd(const GameObjectExitCmd&) = delete;
	GameObjectExitCmd& operator=(const GameObject&) = delete;
	~GameObjectExitCmd() = default;

	void Execute() override;
}; 

#endif _GameObjectExitCmd
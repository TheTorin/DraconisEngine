#include "GameObjectExitCmd.h"
#include "GameObjectAttorney.h"

GameObjectExitCmd::GameObjectExitCmd(GameObject* go)
	:gameObj(go)
{

}

void GameObjectExitCmd::Execute()
{
	GameObjectAttorney::SceneChange::DisconnectFromScene(gameObj);
}
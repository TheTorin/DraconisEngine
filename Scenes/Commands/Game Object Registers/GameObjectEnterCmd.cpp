#include "GameObjectEnterCmd.h"
#include "GameObjectAttorney.h"

GameObjectEnterCmd::GameObjectEnterCmd(GameObject* go)
	:gameObj(go)
{

}

void GameObjectEnterCmd::Execute()
{
	GameObjectAttorney::SceneChange::ConnectToScene(gameObj);
}
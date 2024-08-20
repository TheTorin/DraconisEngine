#ifndef _GameObjectAttorney
#define _GameObjectAttorney

#include "GameObject.h"

class GameObjectAttorney
{
public:
	class SceneChange
	{
		friend class GameObjectEnterCmd;
		friend class GameObjectExitCmd;
	private:
		static void ConnectToScene(GameObject* go) { go->ConnectToScene(); };
		static void DisconnectFromScene(GameObject* go) { go->DisconnectFromScene(); };
	};
};

#endif _GameObjectAttorney
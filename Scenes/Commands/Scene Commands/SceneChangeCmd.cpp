#include "SceneChangeCmd.h"
#include "SceneManagerAttorney.h"

void SceneChangeCmd::Execute()
{
	SceneManagerAttorney::SceneChanging::changeScene(s);
}

void SceneChangeCmd::changeHeldScene(Scene* ns)
{
	s = ns;
}

Scene* SceneChangeCmd::getHeldScene()
{
	return s;
}
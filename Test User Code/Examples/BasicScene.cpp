#include "BasicScene.h"

void BasicScene::Initialize()
{
	box = new BasicBox();
}

void BasicScene::SceneEnd()
{
	delete box;
}
#include "Menu.h"
#include "..//DraconisEngine/Draconis.h"
#include "LevelManager.h"

void Menu::Initialize()
{
	Draconis::setClear(0.0f, 0.48f, 1.0f, 1.0f);
	dt = new DemoTank();
	LevelManager::Initialize();
}

void Menu::SceneEnd()
{
	delete dt;
}
#include "LevelManager.h"
#include "Menu.h"
#include "LevelOne.h"
#include "LevelThree.h"
#include "LevelTwo.h"

LevelManager* LevelManager::ptrInstance = nullptr;

void LevelManager::Initialize()
{
	Instance().currentLevel = 1;
}

void LevelManager::PrivNextLevel()
{
	switch (currentLevel)
	{
	case 0:
		SceneManager::setNextScene(new LevelOne());
		break;
	case 1:
		SceneManager::setNextScene(new LevelTwo());
		break;
	case 2:
		SceneManager::setNextScene(new LevelThree());
		break;
	case 3:
		SceneManager::setNextScene(new Menu());
		currentLevel = 1;
		break;
	default:
		throw new std::invalid_argument("SOMETHING WENT WRONG IN LEVEL MANAGER SWITCH STATEMENT");
		break;
	}
	++currentLevel;
}

void LevelManager::PrivLose()
{
	SceneManager::setNextScene(new Menu());
	currentLevel = 1;
}

void LevelManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
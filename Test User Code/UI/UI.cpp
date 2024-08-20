#include "UI.h"
#include "..//DraconisEngine/Draconis.h"
#include "PlayerManager.h"
#include "BotManager.h"
#include "BuildingManager.h"
#include "BossManager.h"
#include "..//DraconisEngine/SpriteString.h"
#include "..//DraconisEngine/SpriteFontManager.h"
#include "UIBuild.h"
#include "UIBots.h"
#include "UIBoss.h"
#include "LevelManager.h"

UI::UI()
{
	sf = SpriteFontManager::Get("Elephant");
	string = new SpriteString(sf, "", 0, 0);
	healthX = 3 * ((float)Draconis::getWindowWidth() / 4.0f);
	healthY = 50;
	goalPosX = 20;
	goalPosY = 50;
	gameOver = false;

	currentGoal = new UIBuild();

	SubmitDrawRegistration(); 
}

void UI::Draw2D()
{
	if (!gameOver)
	{
		int hp = PlayerManager::getPlayerHP();
		if (hp <= 0)
		{
			GameLose();
		}
		else
		{
			string->Set(sf, "Health: " + std::to_string(hp), healthX, healthY);
			string->Render();
			currentGoal->DrawGoal(this);
		}
	}
	else string->Render();
}

void UI::GameLose()
{
	if (!gameOver) 
	{
		SubmitAlarmRegistration(AlarmableManager::ALARM_1, 2.0f);
		string->Set(sf, "You Lose!", 0, 0);
		string->Set(((float)Draconis::getWindowWidth() / 2) - (string->GetWidth() / 2), ((float)Draconis::getWindowHeight() / 2) - (string->GetHeight() / 2));
	}
	gameOver = true;
}

void UI::GameWin()
{
	if (!gameOver)
	{
		SubmitAlarmRegistration(AlarmableManager::ALARM_0, 2.0f);
		string->Set(sf, "Level Complete!", 0, 0);
		string->Set(((float)Draconis::getWindowWidth() / 2) - (string->GetWidth() / 2), ((float)Draconis::getWindowHeight() / 2) - (string->GetHeight() / 2));
	}
	gameOver = true;
}

void UI::FinalWin()
{
	if (!gameOver)
	{
		SubmitAlarmRegistration(AlarmableManager::ALARM_0, 4.0f);
		string->Set(sf, "YOU WON!", 0, 0);
		string->Set(((float)Draconis::getWindowWidth() / 2) - (string->GetWidth() / 2), ((float)Draconis::getWindowHeight() / 2) - (string->GetHeight() / 2));
	}
	gameOver = true;
}

void UI::ToggleBotsLeft()
{
	delete currentGoal;
	currentGoal = new UIBots();
}

void UI::ToggleBossHP()
{
	delete currentGoal;
	currentGoal = new UIBoss();
}

void UI::ToggleBuildingsLeft()
{
	delete currentGoal;
	currentGoal = new UIBuild();
}

void UI::DrawBotsLeft()
{
	int botsLeft = BotManager::GetBotsLeft();
	if (botsLeft <= 0)
	{
		GameWin();
	}
	else
	{
		string->Set(sf, "Enemies Left: " + std::to_string(botsLeft), goalPosX, goalPosY);
		string->Render();
	}
}

void UI::DrawBossHP()
{
	int health = BossManager::GetHealth();
	if (health <= 0)
	{
		FinalWin();
	}
	else
	{
		string->Set(sf, "Boss HP: " + std::to_string(health), goalPosX, goalPosY);
		string->Render();
	}
}

void UI::DrawBuildingsLeft()
{
	int buildingsLeft = BuildingManager::RemainingBuildings();
	if (buildingsLeft <= 0)
	{
		GameWin();
	}
	else
	{
		string->Set(sf, "Buildings Left: " + std::to_string(buildingsLeft), goalPosX, goalPosY);
		string->Render();
	}
}

void UI::Alarm0()
{
	LevelManager::NextLevel();
}

void UI::Alarm1()
{
	LevelManager::Lose();
}

UI::~UI()
{
	delete string;
	delete currentGoal;
}
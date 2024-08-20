#ifndef _UI
#define _UI

#include "..//DraconisEngine/GameObject.h"

class UIGoal;
class SpriteFont;
class SpriteString;
class UI : public GameObject
{
private:
	UIGoal* currentGoal;
	SpriteFont* sf;
	SpriteString* string;
	float healthX;
	float healthY;
	float goalPosX;
	float goalPosY;
	bool gameOver;

public:
	UI();
	UI(const UI&) = delete;
	UI& operator=(const UI&) = delete;
	~UI();

	void Draw2D() override;

	void Alarm0() override;
	void Alarm1() override;

	void GameLose();
	void GameWin();
	void FinalWin();

	void ToggleBotsLeft();
	void ToggleBossHP();
	void ToggleBuildingsLeft();

	void DrawBotsLeft();
	void DrawBossHP();
	void DrawBuildingsLeft();
};

#endif _UI
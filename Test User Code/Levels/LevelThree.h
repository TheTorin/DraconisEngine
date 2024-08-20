#ifndef _LevelThree
#define _LevelThree

#include "..//DraconisEngine/SceneBase.h"
#include "UI.h"
#include "BossBuilding.h"
#include "Building.h"
#include "PlaneBotManager.h"
#include "AIBotSpawner.h"

class LevelThree : public Scene
{
private:
	UI* ui;
	Building* b1;
	BossBuilding* boss;
	PlaneBotManager* planeManager;
	AIBotSpawner* botSpawner;

public:
	LevelThree() = default;
	LevelThree(const LevelThree&) = delete;
	LevelThree& operator=(const LevelThree&) = delete;
	~LevelThree() = default;

	void Initialize() override;
	void SceneEnd() override;
};

#endif _LevelThree
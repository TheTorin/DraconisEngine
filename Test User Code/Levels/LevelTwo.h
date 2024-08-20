#ifndef _LevelTwo
#define _LevelTwo

#include "..//DraconisEngine/SceneBase.h"
#include "UI.h"
#include "Building.h"

class LevelTwo : public Scene
{
private:
	UI* ui;
	static const int BuildingsX = 9;
	static const int BuildingsZ = 9;
	static const int NumBuildings = BuildingsX * BuildingsZ;
	const float startX = -1802;
	const float startZ = -1611;
	const float endX = 719;
	const float endZ = 1867;
	Building* Buildings[NumBuildings];

public:
	LevelTwo() = default;
	LevelTwo(const LevelTwo&) = delete;
	LevelTwo& operator=(const LevelTwo&) = delete;
	~LevelTwo() = default;

	void Initialize() override;
	void SceneEnd() override;
};

#endif _LevelTwo
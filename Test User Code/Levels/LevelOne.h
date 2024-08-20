#ifndef _LevelOne
#define _LevelOne

#include "..//DraconisEngine/SceneBase.h"
#include "UI.h"
#include "Building.h"

class LevelOne : public Scene
{
private:
	UI* gobj1;
	Building* build1;
	Building* build2;
	Building* build3;

public:
	LevelOne() = default;
	LevelOne(const LevelOne&) = delete;
	LevelOne& operator=(const LevelOne&) = delete;
	~LevelOne() = default;

	void Initialize() override;
	void SceneEnd() override;
};

#endif _LevelOne
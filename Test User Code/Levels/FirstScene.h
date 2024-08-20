#ifndef _FirstScene
#define _FirstScene

#include "../DraconisEngine/SceneBase.h"
#include "WorldPlane.h"
#include "BillboardTest.h"
#include "PlaneBot.h"
#include "UI.h"
#include "Building.h"

class FirstScene : public Scene
{
public:
	FirstScene() = default;
	FirstScene(const FirstScene&) = delete;
	FirstScene& operator=(const FirstScene&) = delete;
	~FirstScene() = default;

	void Initialize() override;
	void SceneEnd() override;

private:

	UI* gobj1;
	WorldPlane* gobj2;
	BillboardTest* gobj3;
	PlaneBot* gobj4;
	Building* build1;
};

#endif _FirstScene
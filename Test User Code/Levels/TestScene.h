#ifndef _TestScene
#define _TestScene

#include "../DraconisEngine/SceneBase.h"

class TestScene : public Scene
{
private:

public:
	TestScene() = default;
	TestScene(const TestScene&) = delete;
	TestScene& operator=(const TestScene&) = delete;
	~TestScene() = default;

	void Initialize() override;
	void SceneEnd() override;
};

#endif _TestScene
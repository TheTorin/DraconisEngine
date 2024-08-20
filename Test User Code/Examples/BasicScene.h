#ifndef _BasicScene
#define _BasicScene

#include "..//DraconisEngine/SceneBase.h"
#include "BasicBox.h"

class BasicScene : public Scene
{
private:
	BasicBox* box;

public:
	BasicScene() = default;
	BasicScene(const BasicScene&) = delete;
	BasicScene& operator=(const BasicScene&) = delete;
	~BasicScene() = default;

	void Initialize() override;
	void SceneEnd() override;
};

#endif _BasicScene
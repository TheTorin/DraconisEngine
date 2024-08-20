#ifndef _Menu
#define _Menu

#include "..//DraconisEngine/SceneBase.h"
#include "DemoTank.h"

class Menu : public Scene
{
private:
	DemoTank* dt;

public:
	Menu() = default;
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
	~Menu() = default;

	void Initialize() override;
	void SceneEnd() override;
};

#endif _Menu
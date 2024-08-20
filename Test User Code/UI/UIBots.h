#ifndef _UIBots
#define _UIBots

#include "UIGoal.h"

class UIBots : public UIGoal
{
public:
	UIBots() = default;
	UIBots(const UIBots&) = delete;
	UIBots& operator=(const UIBots&) = delete;
	~UIBots() = default;

	void DrawGoal(UI* ui) override;
};

#endif _UIBots
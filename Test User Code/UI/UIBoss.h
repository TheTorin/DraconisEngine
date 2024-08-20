#ifndef _UIBoss
#define _UIBoss

#include "UIGoal.h"

class UIBoss : public UIGoal
{
public:
	UIBoss() = default;
	UIBoss(const UIBoss&) = delete;
	UIBoss& operator=(const UIBoss&) = delete;
	~UIBoss() = default;

	void DrawGoal(UI* ui) override;
};

#endif _UIBoss
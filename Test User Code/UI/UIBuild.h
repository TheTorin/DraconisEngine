#ifndef _UIBuild
#define _UIBuild

#include "UIGoal.h"

class UIBuild : public UIGoal
{
public:
	UIBuild() = default;
	UIBuild(const UIBuild&) = delete;
	UIBuild& operator=(const UIBuild&) = delete;
	~UIBuild() = default;

	void DrawGoal(UI* ui) override;
};

#endif _UIBuild
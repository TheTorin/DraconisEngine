#ifndef _UIGoal
#define _UIGoal

class UI;
class UIGoal
{
public:
	UIGoal() = default;
	UIGoal(const UIGoal&) = delete;
	UIGoal& operator=(const UIGoal&) = delete;
	~UIGoal() = default;

	virtual void DrawGoal(UI* ui) = 0;
};

#endif _UIGoal
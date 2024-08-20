#ifndef _GoalCheckBase
#define _GoalCheckBase

class GoalCheckBase
{
public:
	GoalCheckBase() = default;
	GoalCheckBase(const GoalCheckBase&) = delete;
	GoalCheckBase& operator=(const GoalCheckBase&) = delete;
	~GoalCheckBase() = default;

	virtual void Check() = 0;
};

#endif _GoalCheckBase
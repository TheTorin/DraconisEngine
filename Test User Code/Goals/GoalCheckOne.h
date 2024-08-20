#ifndef _GoalCheckOne
#define _GoalCheckOne

#include "GoalCheckBase.h"

class GoalCheckOne : public GoalCheckBase
{
public:
	GoalCheckOne() = default;
	GoalCheckOne(const GoalCheckOne&) = delete;
	GoalCheckOne& operator=(const GoalCheckOne&) = delete;
	~GoalCheckOne() = default;

	void Check() override;
};

#endif _GoalCheckOne
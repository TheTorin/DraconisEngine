#ifndef _PlaneBotManager
#define _PlaneBotManager

#include "..//DraconisEngine/GameObject.h"

class PlaneBotManager : public GameObject
{
private:

public:
	PlaneBotManager();
	PlaneBotManager(const PlaneBotManager&) = delete;
	PlaneBotManager& operator=(const PlaneBotManager&) = delete;
	~PlaneBotManager() = default;

	void Alarm0() override;
};

#endif _PlaneBotManager
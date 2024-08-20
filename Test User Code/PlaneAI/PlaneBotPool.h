#ifndef _PlaneBotPool
#define _PlaneBotPool

#include <stack>
#include <list>

class PlaneBot;
class PlaneBotPool
{
private:
	std::list<PlaneBot*> activePlanes;
	std::stack<PlaneBot*> recycledPlanes;

public:
	PlaneBotPool() = default;
	PlaneBotPool(const PlaneBotPool&) = delete;
	PlaneBotPool& operator=(const PlaneBotPool&) = delete;
	~PlaneBotPool();

	PlaneBot* GetPlane();

	void ReturnPlane(PlaneBot* p);
	void Terminate();
};

#endif _PlaneBotPool
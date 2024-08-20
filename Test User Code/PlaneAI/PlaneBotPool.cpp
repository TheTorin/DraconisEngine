#include "PlaneBotPool.h"
#include "PlaneBot.h"

PlaneBot* PlaneBotPool::GetPlane()
{
	PlaneBot* p;

	if (recycledPlanes.empty())
	{
		p = new PlaneBot();
	}
	else
	{
		p = recycledPlanes.top();
		recycledPlanes.pop();
	}
	activePlanes.push_back(p);
	return p;
}

void PlaneBotPool::ReturnPlane(PlaneBot* p)
{
	recycledPlanes.push(p);
	activePlanes.remove(p);
}

void PlaneBotPool::Terminate()
{
	while (!activePlanes.empty())
	{
		PlaneBot* p = activePlanes.front();
		p->SubmitExit();
		activePlanes.pop_front();
		recycledPlanes.push(p);
	}
}

PlaneBotPool::~PlaneBotPool()
{
	while (!recycledPlanes.empty())
	{
		delete recycledPlanes.top();
		recycledPlanes.pop();
	}
	while (!activePlanes.empty())
	{
		assert(false && "Active plane pool not empty");
	}
}
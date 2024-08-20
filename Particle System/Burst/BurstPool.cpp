#include "BurstPool.h"
#include "Burst.h"

Burst* BurstPool::getBurst()
{
	Burst* b;

	if (recycledBursts.empty())
	{
		b = new Burst();
	}
	else
	{
		b = recycledBursts.top();
		recycledBursts.pop();
	}
	activeBursts.push_back(b);
	return b;
}

void BurstPool::returnBurst(Burst* b)
{
	recycledBursts.push(b);
	activeBursts.remove(b);
}

BurstPool::~BurstPool()
{
	while (!recycledBursts.empty())
	{
		delete recycledBursts.top();
		recycledBursts.pop();
	}
	while (!activeBursts.empty())
	{
		delete activeBursts.front();
		activeBursts.pop_front();
	}
}
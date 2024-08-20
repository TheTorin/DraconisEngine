#include "BombPool.h"
#include "Bomb.h"

Bomb* BombPool::getBomb()
{
	Bomb* b;
	if (recycledBombs.empty())
	{
		b = new Bomb();
	}
	else
	{
		b = recycledBombs.top();
		recycledBombs.pop();
	}
	activeBombs.push_back(b);
	return b;
}

void BombPool::returnBomb(Bomb* b)
{
	activeBombs.remove(b);
	recycledBombs.push(b);
}

void BombPool::Terminate()
{
	while (!activeBombs.empty())
	{
		Bomb* b = activeBombs.front();
		b->SubmitExit();
		activeBombs.pop_front();
		recycledBombs.push(b);
	}
}

BombPool::~BombPool()
{
	while (!recycledBombs.empty())
	{
		delete recycledBombs.top();
		recycledBombs.pop();
	}
	if (!activeBombs.empty())
	{
		assert(false && "ACTIVE BOMB POOL NOT EMPTY AAAAAAAAAAAAAAAAA");
	}
}
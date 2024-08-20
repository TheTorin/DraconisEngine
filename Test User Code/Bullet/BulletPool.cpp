#include "BulletPool.h"
#include "Bullet.h"

Bullet* BulletPool::getBullet()
{
	Bullet* b;

	if (recycledItems.empty())
	{
		//DebugMsg::out("Creating new bullet!\n");
		b = new Bullet();
	}
	else
	{
		//DebugMsg::out("Using recycled bullet!\n");
		b = recycledItems.top();
		recycledItems.pop();
	}
	activeBullets.push_back(b);
	return b;
}

void BulletPool::returnBullet(Bullet* b)
{
	recycledItems.push(static_cast<Bullet*>(b));
	activeBullets.remove(b);
}

void BulletPool::Terminate()
{
	while (!activeBullets.empty())
	{
		Bullet* b = activeBullets.front();
		b->SubmitExit();
		activeBullets.pop_front();
		recycledItems.push(b);
	}
}

BulletPool::~BulletPool()
{
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
	while (!activeBullets.empty())
	{
		assert(false && "ACTIVE BULLET POOL NOT EMPTY AAAAAAAAAAAAAAAAA");
	}
}
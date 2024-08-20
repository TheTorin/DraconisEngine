#ifndef _BulletPool
#define _BulletPool

#include <stack>
#include <list>

class Bullet;
class BulletPool
{
private:
	std::list<Bullet*> activeBullets;
	std::stack<Bullet*> recycledItems;

public:
	BulletPool() = default;
	BulletPool(const BulletPool&) = delete;
	BulletPool& operator=(const BulletPool&) = delete;
	~BulletPool();

	Bullet* getBullet();

	void returnBullet(Bullet* b);
	void Terminate();
};

#endif _BulletPool
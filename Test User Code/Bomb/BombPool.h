#ifndef _BombPool
#define _BombPool

#include <stack>
#include <list>

class Bomb;
class BombPool
{
private:
	std::list<Bomb*> activeBombs;
	std::stack<Bomb*> recycledBombs;

public:
	BombPool() = default;
	BombPool(const BombPool&) = delete;
	BombPool& operator=(const BombPool&) = delete;
	~BombPool();

	Bomb* getBomb();
	void returnBomb(Bomb* b);
	void Terminate();
};

#endif _BombPool
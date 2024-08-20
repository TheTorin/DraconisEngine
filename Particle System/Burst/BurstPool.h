#ifndef _BurstPool
#define _BurstPool

#include <stack>
#include <list>

class Burst;
class BurstPool
{
private:
	std::stack<Burst*> recycledBursts;
	std::list<Burst*> activeBursts;

public:
	BurstPool() = default;
	BurstPool(const BurstPool&) = delete;
	BurstPool& operator=(const BurstPool&) = delete;
	~BurstPool();

	Burst* getBurst();
	void returnBurst(Burst* b);
};

#endif _BurstPool
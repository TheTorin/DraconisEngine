#ifndef _BurstFactory
#define _BurstFactory

#include "BurstPool.h"

class BurstFactory
{
private:
	static BurstFactory* ptrInstance;

	BurstFactory() = default;
	BurstFactory(const BurstFactory&) = delete;
	BurstFactory& operator=(const BurstFactory&) = delete;
	~BurstFactory() = default;

	static BurstFactory& Instance()
	{
		if (!ptrInstance) ptrInstance = new BurstFactory();
		return *ptrInstance;
	}

	BurstPool pool;

	Burst* privCreateBurst();
	void privRecycleBurst(Burst* b);

public:
	static Burst* createBurst() { return Instance().privCreateBurst(); };
	static void recycleBurst(Burst* b) { Instance().privRecycleBurst(b); };
	static void Terminate();
};

#endif _BurstFactory
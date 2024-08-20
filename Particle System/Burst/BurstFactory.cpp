#include "BurstFactory.h"

BurstFactory* BurstFactory::ptrInstance = nullptr;

Burst* BurstFactory::privCreateBurst()
{
	return pool.getBurst();
}

void BurstFactory::privRecycleBurst(Burst* b)
{
	pool.returnBurst(b);
}

void BurstFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
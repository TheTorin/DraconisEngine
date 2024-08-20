#ifndef _BossManager
#define _BossManager

#include "BossBuilding.h"

class BossManager
{
private:
	static BossManager* ptrInstance;

	BossManager() = default;
	BossManager(const BossManager&) = delete;
	BossManager& operator=(const BossManager&) = delete;
	~BossManager() = default;

	static BossManager& Instance()
	{
		if (!ptrInstance) ptrInstance = new BossManager();
		return *ptrInstance;
	}

	BossBuilding* boss;

public:
	static void Register(BossBuilding* b) { Instance().boss = b; };
	static int GetHealth() { return Instance().boss->GetHealth(); };
	static void Terminate();
};

#endif _BossManager
#ifndef _BuildingManager
#define _BuildingManager

#include <vector>

class Building;
class BuildingManager
{
private:
	static BuildingManager* ptrInstance;

	BuildingManager() = default;
	BuildingManager(const BuildingManager&) = delete;
	BuildingManager& operator=(const BuildingManager&) = delete;
	~BuildingManager() = default;

	static BuildingManager& Instance()
	{
		if (!ptrInstance) ptrInstance = new BuildingManager();
		return *ptrInstance;
	}

	int numBuildings;

public:
	static void AddBuilding() { Instance().numBuildings++; };
	static void RemoveBuilding() { Instance().numBuildings--; };
	static int RemainingBuildings() { return Instance().numBuildings; };
	static void Terminate();
};

#endif _BuildingManager
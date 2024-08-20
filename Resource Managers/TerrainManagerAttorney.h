#ifndef _TerrainManagerAttorney
#define _TerrainManagerAttorney

#include "TerrainManager.h"

class TerrainManagerAttorney
{
	friend class Draconis;
private:
	static void Terminate() { TerrainManager::Terminate(); };
};

#endif _TerrainManagerAttorney
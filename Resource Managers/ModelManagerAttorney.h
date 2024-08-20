#ifndef _ModelManagerAttorney
#define _ModelManagerAttorney

#include "ModelManager.h"

class ModelManagerAttorney
{
	friend class Draconis;
private:
	static void Terminate() { ModelManager::Terminate(); };
};

#endif _ModelManagerAttorney
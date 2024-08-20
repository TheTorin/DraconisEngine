#ifndef _ShaderManagerAttorney
#define _ShaderManagerAttorney

#include "ShaderManager.h"

class ShaderManagerAttorney
{
	friend class Draconis;
private:
	static void Terminate() { ShaderManager::Terminate(); };
};

#endif _ShaderManagerAttorney
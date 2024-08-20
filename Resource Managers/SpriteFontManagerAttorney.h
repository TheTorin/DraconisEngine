#ifndef _SpriteFontManagerAttorney
#define _SpriteFontManagerAttorney

#include "SpriteFontManager.h"

class SpriteFontManagerAttorney
{
	friend class Draconis;
private:
	static void Terminate() { SpriteFontManager::Terminate(); };
};

#endif _SpriteFontManagerAttorney
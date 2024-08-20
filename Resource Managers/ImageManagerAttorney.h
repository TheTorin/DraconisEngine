#ifndef _ImageManagerAttorney
#define _ImageManagerAttorney

#include "ImageManager.h"

class ImageManagerAttorney
{
	friend class Draconis;
private:
	static void Terminate() { ImageManager::Terminate(); };
};

#endif _ImageManagerAttorney
#ifndef _Color
#define _Color

#include "AzulCore.h"

namespace Color
{
	static const Vect Black = Vect(0, 0, 0, 1);
	static const Vect White = Vect(1, 1, 1, 1);
	static const Vect LightGray = Vect(0.75f, 0.75f, 0.75f, 1);
	static const Vect DarkGray = Vect(0.5f, 0.5f, 0.5f, 1);

	static const Vect Red = Vect(1, 0, 0, 1);
	static const Vect Green = Vect(0, 1, 0, 1);
	static const Vect Blue = Vect(0, 0, 1, 1);

	static const Vect Pink = Vect(1, 0.5f, 0.5f, 1);
	static const Vect LightGreen = Vect(0.5f, 1, 0.5f, 1);
	static const Vect LightBlue = Vect(0.5f, 0.5f, 1, 1);
	static const Vect DarkRed = Vect(0.5f, 0, 0, 1);
	static const Vect DarkGreen = Vect(0, 0.5f, 0, 1);
	static const Vect DarkBlue = Vect(0, 0, 0.5f, 1);

	static const Vect Magenta = Vect(1, 0, 1, 1);
	static const Vect Yellow = Vect(1, 1, 0, 1);
	static const Vect Turquoise = Vect(0, 1, 1, 1);
}

#endif _Color
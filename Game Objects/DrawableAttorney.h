#ifndef _DrawableAttorney
#define _DrawableAttorney

#include "Drawable.h"

class DrawableAttorney
{
public:
	class DrawLoop
	{
		friend class DrawableManager;
	private:
		static void Draw(Drawable* draw) { draw->Draw(); };
		static void Draw2D(Drawable* draw) { draw->Draw2D(); };
	};

	class Registration
	{
		friend class DrawRegisterCmd;
		friend class DrawDeregisterCmd;
	private:
		static void DrawRegister(Drawable* draw) { draw->DrawRegistration(); };
		static void DrawDeregister(Drawable* draw) { draw->DrawDeregistration(); };
	};
};

#endif _DrawableAttorney
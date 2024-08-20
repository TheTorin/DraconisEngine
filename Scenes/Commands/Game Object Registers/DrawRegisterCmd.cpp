#include "DrawRegisterCmd.h"
#include "DrawableAttorney.h"

DrawRegisterCmd::DrawRegisterCmd(Drawable* draw)
	:ptrDraw(draw)
{

}

void DrawRegisterCmd::Execute()
{
	DrawableAttorney::Registration::DrawRegister(ptrDraw);
}
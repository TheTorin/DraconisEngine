#include "DrawDeregisterCmd.h"
#include "DrawableAttorney.h"

DrawDeregisterCmd::DrawDeregisterCmd(Drawable* draw)
	:ptrDraw(draw)
{

}

void DrawDeregisterCmd::Execute()
{
	DrawableAttorney::Registration::DrawDeregister(ptrDraw);
}
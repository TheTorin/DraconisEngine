#ifndef _DrawRegisterCmd
#define _DrawRegisterCmd

#include "SceneCommandBase.h"

class Drawable;
class DrawRegisterCmd : public SceneCommandBase
{
private:
	Drawable* ptrDraw;

public:
	DrawRegisterCmd(Drawable* draw);
	DrawRegisterCmd(const DrawRegisterCmd&) = delete;
	DrawRegisterCmd& operator=(const DrawRegisterCmd&) = delete;
	~DrawRegisterCmd() = default;

	void Execute() override;
};

#endif _DrawRegisterCmd
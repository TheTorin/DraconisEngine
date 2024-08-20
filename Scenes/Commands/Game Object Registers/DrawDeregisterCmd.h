#ifndef _DrawDeregisterCmd
#define _DrawDeregisterCmd

#include "SceneCommandBase.h"

class Drawable;
class DrawDeregisterCmd : public SceneCommandBase
{
private:
	Drawable* ptrDraw;

public:
	DrawDeregisterCmd(Drawable* draw);
	DrawDeregisterCmd(const DrawDeregisterCmd&) = delete;
	DrawDeregisterCmd& operator=(const DrawDeregisterCmd&) = delete;
	~DrawDeregisterCmd() = default;

	void Execute() override;
};

#endif _DrawDeregisterCmd
#ifndef _UpdateRegisterCmd
#define _UpdateRegisterCmd

#include "SceneCommandBase.h"

class Updateable;
class UpdateRegisterCmd : public SceneCommandBase
{
private:
	Updateable* ptrUp;
public:
	UpdateRegisterCmd(Updateable* up);
	UpdateRegisterCmd(const UpdateRegisterCmd&) = delete;
	UpdateRegisterCmd& operator=(const UpdateRegisterCmd&) = delete;
	~UpdateRegisterCmd() = default;

	void Execute() override;
};

#endif _UpdateRegisterCmd
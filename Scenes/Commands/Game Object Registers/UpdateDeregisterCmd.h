#ifndef _UpdateDeregisterCmd
#define _UpdateDeregisterCmd

#include "SceneCommandBase.h"

class Updateable;
class UpdateDeregisterCmd : public SceneCommandBase
{
private:
	Updateable* ptrUp;

public:
	UpdateDeregisterCmd(Updateable* up);
	UpdateDeregisterCmd(const UpdateDeregisterCmd&) = delete;
	UpdateDeregisterCmd& operator=(const UpdateDeregisterCmd&) = delete;
	~UpdateDeregisterCmd() = default;

	void Execute() override;
};

#endif _UpdateDeregisterCmd
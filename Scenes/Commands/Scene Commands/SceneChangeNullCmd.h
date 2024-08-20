#ifndef _SceneChangeNullCmd
#define _SceneChangeNullCmd

#include "SceneChangeCmdBase.h"

class SceneChangeNull : public SceneChangeBase
{
public:
	SceneChangeNull() = default;
	SceneChangeNull(const SceneChangeNull&) = delete;
	SceneChangeNull& operator=(const SceneChangeNull&) = delete;
	~SceneChangeNull() = default;

	virtual void Execute() {};
};

#endif _SceneChangeNullCmd
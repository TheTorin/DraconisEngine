#ifndef _SceneNull
#define _SceneNull

#include "SceneBase.h"

class SceneNull : public Scene
{
private:
	virtual void Initialize() {};
	virtual void SceneEnd() {};
};

#endif _SceneNull
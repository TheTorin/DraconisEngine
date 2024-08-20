#ifndef _SpriteTest
#define _SpriteTest

#include "..//DraconisEngine/GameObject.h"

class SpriteTest : public GameObject
{
private:
	GraphicsObject_Sprite* sprite;
	Matrix rot;
	Matrix scale;
	Vect pos;
	float currAngle;

public:
	SpriteTest();
	SpriteTest(const SpriteTest&) = delete;
	SpriteTest & operator=(const SpriteTest&) = delete;
	~SpriteTest();

	void Draw() override;
};

#endif _SpriteTest
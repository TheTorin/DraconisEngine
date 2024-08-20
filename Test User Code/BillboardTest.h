#ifndef _BillboardTest
#define _BillboardTest

#include "..//DraconisEngine/GameObject.h"

class BillboardTest : public GameObject
{
private:
	GraphicsObject_TextureFlat* sprite;
	Matrix rot;
	Matrix scale;
	Vect pos;

public:
	BillboardTest();
	BillboardTest(const BillboardTest&) = delete;
	BillboardTest& operator=(const BillboardTest&) = delete;
	~BillboardTest();

	void Update() override;
	void Draw() override;
};

#endif _BillboardTest
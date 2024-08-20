#include "BillboardTest.h"
#include "..//DraconisEngine/Visualizer.h"

BillboardTest::BillboardTest()
{
	sprite = new GraphicsObject_TextureFlat(ModelManager::Get("Square"), ShaderManager::Get("ObjTex"), TextureManager::Get("Raindrop"));
	rot = Matrix(IDENTITY);
	scale = Matrix(SCALE, Vect(10, 10, 10));
	pos = Vect(0, 80, 0);

	Matrix world = rot * scale * Matrix(TRANS, pos);
	sprite->SetWorld(world);

	SubmitDrawRegistration();
}

void BillboardTest::Update()
{

}

void BillboardTest::Draw()
{
	Vect camPos;
	Vect rightTest;
	SceneManager::getCurrentScene()->getCurrentCamera()->getRight(rightTest);
	SceneManager::getCurrentScene()->getCurrentCamera()->getPos(camPos);

	//camPos.set(camPos.X(), 80, camPos.Z());
	Vect toCam = camPos - pos;
	toCam.norm();
	toCam.set(toCam.X(), toCam.Y(), toCam.Z(), 0);
	Vect toCross = toCam + rightTest;
	Vect up = toCam.cross(toCross);
	up.set(up.X(), up.Y(), up.Z(), 0);
	//Vect up = Vect(0, 1, 0, 0);
	Vect side = toCam.cross(up);
	side.set(side.X(), side.Y(), side.Z(), 0);

	rot = Matrix(side, up, toCam, Vect(0, 0, 0, 1));

	Matrix world = rot * scale * Matrix(TRANS, pos);
	sprite->SetWorld(world);

	sprite->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

BillboardTest::~BillboardTest()
{
	delete sprite;
}
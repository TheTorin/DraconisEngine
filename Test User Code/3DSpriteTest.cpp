#include "3DSpriteTest.h"

SpriteTest::SpriteTest()
{
	ImageManager::Load("Firelion", TextureManager::Get("Firelion"));
	sprite = new GraphicsObject_Sprite(ModelManager::Get("Square"), ShaderManager::Get("ObjTex"), ImageManager::Get("Firelion"), new Rect(0.0f, 0.0f, 128.0f, 128.0f));
	rot = Matrix(IDENTITY);
	scale = Matrix(SCALE, Vect(10, 10, 10));
	pos = Vect(1000, 250, -1000);

	Matrix world = rot * scale * Matrix(TRANS, pos);
	sprite->SetWorld(world);

	SubmitDrawRegistration();
	currAngle = 0;
}

void SpriteTest::Draw()
{
	currAngle += MATH_PI_180;
	rot = Matrix(ROT_Y, currAngle);
	Matrix world = rot * scale * Matrix(TRANS, pos);
	sprite->SetWorld(world);
	sprite->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

SpriteTest::~SpriteTest()
{
	delete sprite;
}
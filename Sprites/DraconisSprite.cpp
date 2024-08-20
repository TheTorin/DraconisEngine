#include "DraconisSprite.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"

DraconisSprite::DraconisSprite(const std::string& key)
{
	Image* i = ImageManager::Get(key);
	pGOSprite = new GraphicsObject_Sprite(ModelManager::Get("Square"), ShaderManager::Get("Sprite"), i, i->pImageRect);
	Scale.set(SCALE, 1.0f, 1.0f, 1.0f);
	ZRot.set(ROT_Z, 0.0f);
	angle = 0;
	centerX = pGOSprite->origPosX;
	centerY = pGOSprite->origPosY;
	Pos.set(centerX, centerY, 0.0f);

	scaleX = 1;
	scaleY = 1;

	Matrix world = Scale * ZRot * Matrix(TRANS, Pos);
	pGOSprite->SetWorld(world);
}

DraconisSprite& DraconisSprite::operator=(const DraconisSprite& o)
{
	pGOSprite = new GraphicsObject_Sprite(*o.pGOSprite);
	Scale = o.Scale;
	ZRot = o.ZRot;
	Pos = o.Pos;

	angle = o.angle;
	centerX = o.centerX;
	centerY = o.centerY;
	scaleX = o.scaleX;
	scaleY = o.scaleY;
	return *this;
}

void DraconisSprite::SetAngle(float a)
{
	angle = a;
	ZRot.set(ROT_Z, a);
	Matrix world = Scale * ZRot * Matrix(TRANS, Pos);
	pGOSprite->SetWorld(world);
}

void DraconisSprite::SetCenter(float offsetX, float offsetY)
{
	float tX = Pos.X() - centerX;
	float tY = Pos.Y() - centerY;
	centerX = offsetX;
	centerY = offsetY;
	Pos.set(tX + offsetX, tY + offsetY, 0.0f);

	Matrix world = Scale * ZRot * Matrix(TRANS, Pos);
	pGOSprite->SetWorld(world);
}

void DraconisSprite::SetPosition(float x, float y)
{
	Pos.set(centerX + x, centerY + y, 0.0f);
	Matrix world = Scale * ZRot * Matrix(TRANS, Pos);
	pGOSprite->SetWorld(world);
}

void DraconisSprite::SetScaleFactor(float sX, float sY)
{
	scaleX = sX;
	scaleY = sY;
	Scale.set(SCALE, sX, sY, 1.0f);
	Matrix world = Scale * ZRot * Matrix(TRANS, Pos);
	pGOSprite->SetWorld(world);
}

void DraconisSprite::SetScalePixel(float width, float height)
{
	float sX = width / pGOSprite->origWidth;
	float sY = height / pGOSprite->origHeight;
	scaleX = sX;
	scaleY = sY;
	Scale.set(SCALE, sX, sY, 1.0f);
	Matrix world = Scale * ZRot * Matrix(TRANS, Pos);
	pGOSprite->SetWorld(world);
}

void DraconisSprite::Render()
{
	pGOSprite->Render(SceneManager::getCurrentScene()->get2DCamera());
}

DraconisSprite::~DraconisSprite()
{
	delete pGOSprite;
}
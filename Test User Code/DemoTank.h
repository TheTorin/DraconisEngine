#ifndef _DemoTank
#define _DemoTank

#include "..//DraconisEngine/GameObject.h"

class DraconisSprite;
class SpriteString;
class DemoTank : public GameObject
{
private:
	GraphicsObject_TextureLight* pGObjTankBody;
	GraphicsObject_TextureLight* pGObjTankTurret;
	GraphicsObject_TextureLight* pGObjTankBarrel;
	SpriteString* startText;
	SpriteString* titleText;
	DraconisSprite* background;

	Matrix tankRot;
	Matrix tankScale;
	Vect tankPos;

public:
	DemoTank();
	DemoTank(const DemoTank&) = delete;
	DemoTank& operator=(const DemoTank&) = delete;
	~DemoTank();

	void Update() override;
	void Draw() override;
	void Draw2D() override;

	void KeyPressed(AZUL_KEY k) override;
};

#endif _DemoTank
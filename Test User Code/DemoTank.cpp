#include "DemoTank.h"
#include "..//DraconisEngine/SpriteString.h"
#include "..//DraconisEngine/DraconisSprite.h"
#include "..//DraconisEngine/Draconis.h"
#include "FirstScene.h"
#include "LevelOne.h"

DemoTank::DemoTank()
{
	Vect LightColor(0.50f, 0.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 10.0f, 1.0f, 1.0f);
	pGObjTankBody = new GraphicsObject_TextureLight(ModelManager::Get("TankBody"), ShaderManager::Get("ObjTexLight"),
		TextureManager::Get("Green"), LightColor, LightPos);

	pGObjTankTurret = new GraphicsObject_TextureLight(ModelManager::Get("TankTurret"), ShaderManager::Get("ObjTexLight"), TextureManager::Get("Green"), LightColor, LightPos);
	pGObjTankBarrel = new GraphicsObject_TextureLight(ModelManager::Get("TankBarrel"), ShaderManager::Get("ObjTexLight"), TextureManager::Get("Green"), LightColor, LightPos);

	tankScale.set(SCALE, 10.0f, 10.0f, 10.0f);
	tankRot.set(IDENTITY);
	tankPos.set(0, 0, 0);
	Matrix world = tankScale * tankRot * Matrix(TRANS, tankPos);

	pGObjTankBody->SetWorld(world);
	pGObjTankTurret->SetWorld(world);
	pGObjTankBarrel->SetWorld(world);

	titleText = new SpriteString(SpriteFontManager::Get("Showcard"), "My AWESOME Tank Game", 200, 150);
	titleText->Set(((float)Draconis::getWindowWidth() / 2) - (titleText->GetWidth() / 2), 175);
	startText = new SpriteString(SpriteFontManager::Get("Elephant"), "Press SPACE to play!", 100, 100);
	startText->Set(((float)Draconis::getWindowWidth() / 2) - (startText->GetWidth() / 2), 85);

	background = new DraconisSprite("MenuBG");
	background->SetCenter(0, 0);
	background->SetPosition((float)Draconis::getWindowWidth() / 2, (float)Draconis::getWindowHeight() / 2);
	background->SetScalePixel((float)Draconis::getWindowWidth(), (float)Draconis::getWindowHeight());

	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitInputRegistration(AZUL_KEY::KEY_SPACE, EventType::KEY_PRESSED);
}

void DemoTank::Update()
{
	tankRot *= Matrix(ROT_Y, 0.01f);
	Matrix world = tankScale * tankRot * Matrix(TRANS, tankPos);

	pGObjTankBody->SetWorld(world);
	pGObjTankTurret->SetWorld(world);
	pGObjTankBarrel->SetWorld(world);
}

void DemoTank::KeyPressed(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE)
	{
		SceneManager::setNextScene(new LevelOne());
	}
}

void DemoTank::Draw()
{
	pGObjTankBarrel->Render(SceneManager::getCurrentScene()->getCurrentCamera());
	pGObjTankBody->Render(SceneManager::getCurrentScene()->getCurrentCamera());
	pGObjTankTurret->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

void DemoTank::Draw2D()
{
	background->Render();
	titleText->Render();
	startText->Render();
}

DemoTank::~DemoTank()
{
	delete pGObjTankBarrel;
	delete pGObjTankBody;
	delete pGObjTankTurret;
	delete background;
	delete titleText;
	delete startText;
}
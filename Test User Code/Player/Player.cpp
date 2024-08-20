#include "Player.h"
#include "BulletFactory.h"
#include "../DraconisEngine/Visualizer.h"
#include "..//DraconisEngine/ScreenLog.h"
#include "..//DraconisEngine/Draconis.h"
#include "..//DraconisEngine/Color.h"
#include "..//DraconisEngine/Emitter.h"
#include "..//DraconisEngine/TimeManager.h"

Player::Player()
{
	// Light
	Vect LightColor(0.50f, 0.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 10.0f, 1.0f, 1.0f);
	pGObjTankBody = new GraphicsObject_TextureLight(ModelManager::Get("TankBody"), ShaderManager::Get("ObjTexLight"),
		TextureManager::Get("Green"), LightColor, LightPos);

	pGObjTankTurret = new GraphicsObject_TextureLight(ModelManager::Get("TankTurret"), ShaderManager::Get("ObjTexLight"), TextureManager::Get("Green"), LightColor, LightPos);
	pGObjTankBarrel = new GraphicsObject_TextureLight(ModelManager::Get("TankBarrel"), ShaderManager::Get("ObjTexLight"), TextureManager::Get("Green"), LightColor, LightPos);

	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	pGObjSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ConstantColor"), Blue);

	//TankBody world
	TankScale.set(SCALE, 10.0f, 10.0f, 10.0f);
	TankBodyRot.set(IDENTITY);
	TankPos.set(0, 0, 0);
	Matrix world = TankScale * TankBodyRot * Matrix(TRANS, TankPos);
	pGObjTankBody->SetWorld(world);

	//TankTurret world
	TankTurretRot.set(ROT_Y, 0.0f);
	world = TankScale * TankTurretRot * Matrix(TRANS, TankPos);
	pGObjTankTurret->SetWorld(world);

	//TankBarrel world
	TankBarrelRot.set(ROT_X, 0.0f);
	world = TankScale * (TankTurretRot * TankBarrelRot) * Matrix(TRANS, TankPos);
	CurrBarrelHeight = 0;

	BsphereToggle = false;

	CamShipOffset = Vect(0, 140, -300);
	CamLookAt = Vect(0, 50, 100);

	SubmitUpdateRegistration();
	SubmitDrawRegistration();

	SubmitInputRegistration(AZUL_KEY::KEY_W, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_S, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_A, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_D, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_Q, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_E, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_KP_8, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_KP_2, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_SPACE, EventType::EVENT_TYPE::KEY_PRESSED);

	SetCollidableGroup<Player>();
	SubmitCollisionRegistration();

	SetColliderModel(pGObjTankBody->getModel(), VolumeType::OBB);

	followCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	followCam->setViewport(0, 0, Draconis::getWindowWidth(), Draconis::getWindowHeight());
	followCam->setPerspective(35.0f, float(Draconis::getWindowWidth()) / float(Draconis::getWindowHeight()), 1.0f, 5000.0f);

	SceneManager::getCurrentScene()->setCurrentCamera(followCam);
	//SceneManager::getCurrentScene()->setGodCam();

	hp = 5;
	currentCooldown = 0;
}

Vect Player::getWorldPos()
{
	return worldPos;
}

void Player::SetPos(Vect pos)
{
	TankPos = pos;
}

void Player::KeyHeldDown(AZUL_KEY k)
{
	switch (k)
	{
	case(AZUL_KEY::KEY_W):
		TankPos += Vect(0, 0, 1) * TankBodyRot * ShipTransSpeed * TimeManager::getFrameTime();
		break;
	case(AZUL_KEY::KEY_S):
		TankPos += Vect(0, 0, 1) * TankBodyRot * -ShipTransSpeed * TimeManager::getFrameTime();
		break;
	case(AZUL_KEY::KEY_A):
		TankBodyRot *= Matrix(ROT_Y, ShipRotAng);
		break;
	case(AZUL_KEY::KEY_D):
		TankBodyRot *= Matrix(ROT_Y, -ShipRotAng);
		break;
	case(AZUL_KEY::KEY_Q):
		TankTurretRot *= Matrix(ROT_Y, ShipRotAng);
		break;
	case(AZUL_KEY::KEY_E):
		TankTurretRot *= Matrix(ROT_Y, -ShipRotAng);
		break;
	case(AZUL_KEY::KEY_KP_8):
		if (CurrBarrelHeight > MaxBarrelHeight)
		{
			CurrBarrelHeight -= TurretRotAng;
			TankBarrelRot *= Matrix(ROT_X, -TurretRotAng);
		}
		break;
	case(AZUL_KEY::KEY_KP_2):
		if (CurrBarrelHeight < 0)
		{
			CurrBarrelHeight += TurretRotAng;
			TankBarrelRot *= Matrix(ROT_X, TurretRotAng);
		}
		break;
	default:
		DebugMsg::out("Something went terribly wrong!\n");
	}
}

void Player::KeyPressed(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE && currentCooldown <= 0 && hp > 0) 
	{
		Matrix currRot = TankBarrelRot * TankTurretRot;
		Vect fwd = currRot.get(MatrixRowType::ROW_2);
		Vect up = Vect(0, 22, 0);
		BulletFactory::createBullet(currRot, TankPos + (fwd * 56) + up);
		currentCooldown = maxCooldown;
	}
}

void Player::Update()
{
	if (currentCooldown > 0) currentCooldown -= TimeManager::getFrameTime();

	float currHeight = SceneManager::getCurrentScene()->GetTerrain()->GetHeight(TankPos.X(), TankPos.Z());
	TankPos.set(TankPos.X(), currHeight, TankPos.Z());
	// Spaceship adjust matrix
	Matrix world = TankScale * TankBodyRot * Matrix(TRANS, TankPos);
	pGObjTankBody->SetWorld(world);
	UpdateCollisionData(world);

	world = TankScale * TankTurretRot * Matrix(TRANS, TankPos);
	pGObjTankTurret->SetWorld(world);

	world = TankScale * (TankBarrelRot * TankTurretRot) * Matrix(TRANS, TankPos);
	pGObjTankBarrel->SetWorld(world);

	worldPos = world.get(MatrixRowType::ROW_3);

	//*
	// Placing the camera relative to the spaceship
	Matrix ShipRotPos = TankTurretRot * Matrix(TRANS, TankPos);  // This is the worldmat without scaling
	Vect vNewCamPos = CamLookAt * ShipRotPos;		// This moves the cam position relative to ship's position and rotation
	Vect vNewLookAt = CamShipOffset * ShipRotPos;   // This moves the look-at point relative to ship's position and rotation
	followCam->setOrientAndPosition( Vect(0, 1, 0), vNewCamPos, vNewLookAt);
	followCam->updateCamera();
	//*/
	Vect heightPos = Vect(TankPos.X(), currHeight, TankPos.Z());
	Visualizer::showPoint(heightPos, Color::Yellow);

	Vect currNorm = SceneManager::getCurrentScene()->GetTerrain()->GetNormal(this);
	Visualizer::showLine(heightPos, heightPos + (currNorm * 5), Color::Red);

	ScreenLog::Add("Pos: %.2f, %.2f, %.2f", TankPos.X(), TankPos.Y(), TankPos.Z());
}

void Player::Draw()
{
	pGObjTankBody->Render(SceneManager::getCurrentScene()->getCurrentCamera());
	pGObjTankBarrel->Render(SceneManager::getCurrentScene()->getCurrentCamera());
	pGObjTankTurret->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

void Player::Collision(Bullet*)
{
	DebugMsg::out("Collision with bullet from Player!");
	hp--;
	if (hp == 0)
	{
		TankPos += Vect(0, -100, 0);
		SubmitUpdateDeregistration();
		SubmitDrawDeregistration();
		SubmitCollisionDeregistration();
	}
}

void Player::Collision(Bomb*)
{
	hp -= 2;
	if (hp <= 0)
	{
		TankPos += Vect(0, -100, 0);
		SubmitUpdateDeregistration();
		SubmitDrawDeregistration();
		SubmitCollisionDeregistration();
	}
}

Player::~Player()
{
	delete pGObjTankBody;
	delete pGObjTankTurret;
	delete pGObjTankBarrel;
	delete pGObjSphere;
	delete followCam;
}
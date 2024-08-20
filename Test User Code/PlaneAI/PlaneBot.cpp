#include "PlaneBot.h"
#include "..//DraconisEngine/TimeManager.h"
#include "BombFactory.h"
#include "..//DraconisEngine/DragonMath.h"

PlaneBot::PlaneBot()
{
	botPlane = new GraphicsObject_TextureFlat(ModelManager::Get("Frigate"), ShaderManager::Get("ObjTex"), TextureManager::Get("Frigate"));

	planeRot.set(IDENTITY);
	planeScale.set(IDENTITY);
	planePos.set(0, 0, 0);

	speed = 2.0f;
	pivotDist = 200.0f;

	SetCollidableGroup<PlaneBot>();
	SetColliderModel(botPlane->getModel(), VolumeType::OBB);
}

void PlaneBot::Initialize(Matrix rot, Vect pos)
{
	planeRot = rot;
	planePos = pos;
	isTurning = false;
	angle = 0;
}

void PlaneBot::SceneEntry()
{
	SubmitDrawRegistration();
	SubmitUpdateRegistration();
	SubmitCollisionRegistration();
	SubmitAlarmRegistration(AlarmableManager::ALARM_0, 4.0f);
	SubmitAlarmRegistration(AlarmableManager::ALARM_1, 3.0f);

	Matrix world = planeScale * planeRot * Matrix(TRANS, planePos);
	botPlane->SetWorld(world);

	UpdateCollisionData(world);
}

void PlaneBot::Alarm0()
{
	isTurning = !isTurning;
	float time = 4.0f;
	if (isTurning)
	{
		if (angle >= (halfPi * 4)) angle = 0;
		angleMax = angle + (halfPi * 2);
		time = 2.0f;
		Vect right = planeRot.get(MatrixRowType::ROW_0);
		pivot = planePos + (-right * pivotDist);
	}
	else
	{
		planeRot *= Matrix(ROT_Y, 3.1415f);
	}
	SubmitAlarmRegistration(AlarmableManager::ALARM_0, time);
}

void PlaneBot::Alarm1()
{
	BombFactory::CreateBomb(planePos);
	SubmitAlarmRegistration(AlarmableManager::ALARM_1, 3.0f);
}

void PlaneBot::Update()
{
	Matrix world;
	if (isTurning)
	{
		angle += halfPi * TimeManager::getFrameTime();
		angle = DragonMath::Clamp(angle, -360, angleMax);
		Vect offset = Vect(pivotDist, 0, 0);
		world = planeScale * Matrix(TRANS, offset) * Matrix(ROT_Y, -angle) * Matrix(TRANS, pivot);
		planePos = world.get(MatrixRowType::ROW_3);
	}
	else
	{
		Vect forward = planeRot.get(MatrixRowType::ROW_2);
		planePos += (forward * speed);
		world = planeScale * planeRot * Matrix(TRANS, planePos);
	}

	botPlane->SetWorld(world);
	UpdateCollisionData(world);
}

void PlaneBot::Draw()
{
	botPlane->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

void PlaneBot::Collision(Bullet* other)
{
	other;
	SubmitExit();
}

void PlaneBot::SceneExit()
{
	SubmitDrawDeregistration();
	SubmitUpdateDeregistration();
	SubmitCollisionDeregistration();
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
}

PlaneBot::~PlaneBot()
{
	delete botPlane;
}
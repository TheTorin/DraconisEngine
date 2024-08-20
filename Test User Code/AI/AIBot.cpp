#include "AIBot.h"
#include "BulletFactory.h"
#include "PlayerManager.h"
#include "BotFactory.h"
#include "../DraconisEngine/Visualizer.h"
#include "..//DraconisEngine/Terrain.h"
#include "../DraconisEngine/ParticleEffectManager.h"
#include "..//DraconisEngine/ParticleEffect.h"

AIBot::AIBot()
{
	Vect LightColor(1.5f, 0.0f, 0.0f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	botBody = new GraphicsObject_TextureLight(ModelManager::Get("TankBody"), ShaderManager::Get("ObjTexLight"), TextureManager::Get("Red"), LightColor, LightPos);
	botTurret = new GraphicsObject_TextureLight(ModelManager::Get("TankTurret"), ShaderManager::Get("ObjTexLight"), TextureManager::Get("Red"), LightColor, LightPos);
	botBarrel = new GraphicsObject_TextureLight(ModelManager::Get("TankBarrel"), ShaderManager::Get("ObjTexLight"), TextureManager::Get("Red"), LightColor, LightPos);

	bodyScale.set(SCALE, 10.0f, 10.0f, 10.0f);
	bodyRot.set(IDENTITY);
	bodyPos.set(0.0f, 0.0f, 0.0f);

	turretRot.set(IDENTITY);
	barrelRot.set(IDENTITY);

	moveMult = 1;
	sideMult = 1;

	SetCollidableGroup<AIBot>();
	SetColliderModel(botBody->getModel(), VolumeType::OBB);
}

void AIBot::Initialize(Matrix rot, Vect pos)
{
	bodyRot = rot;
	bodyPos = pos;
}

void AIBot::SceneEntry()
{
	toMove = false;
	moveSide = false;

	SubmitDrawRegistration();
	SubmitUpdateRegistration();
	SubmitCollisionRegistration();
	SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
	SubmitAlarmRegistration(AlarmableManager::ALARM_1, 3.0f);
	SubmitAlarmRegistration(AlarmableManager::ALARM_2, 3.0f);

	Matrix world = bodyScale * bodyRot * Matrix(TRANS, bodyPos);
	botBody->SetWorld(world);

	world = bodyScale * turretRot * Matrix(TRANS, bodyPos);
	botTurret->SetWorld(world);
	botBarrel->SetWorld(world);

	worldPos = world.get(MatrixRowType::ROW_3);
	UpdateCollisionData(world);
}

void AIBot::Alarm0()
{
	toMove = !toMove;
	if (toMove == false) moveMult *= -1;
	SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
}

void AIBot::Alarm1()
{
	Matrix currRot = barrelRot * turretRot;
	Vect fwd = currRot.get(MatrixRowType::ROW_2);
	Vect up = Vect(0, 22, 0);
	BulletFactory::createBullet(currRot, bodyPos + (fwd * 56) + up);
	float time = (rand() % 2) + 1.5f;
	SubmitAlarmRegistration(AlarmableManager::ALARM_1, time);
}

void AIBot::Alarm2()
{
	moveSide = !moveSide;
	if (!moveSide) sideMult *= -1;
	else
	{
		Vect forward = turretRot.get(MatrixRowType::ROW_2);
		Vect right = forward.getNorm().cross(Vect(0, 1, 0));
		sideVect = right * sideMult;
	}

	float time = (rand() % 3) + 2.0f;
	SubmitAlarmRegistration(AlarmableManager::ALARM_2, time);
}

void AIBot::Update()
{
	prevX = bodyPos.X();
	prevZ = bodyPos.Z();

	submitMove = false;
	//Get information about player, position, turret rotation
	Vect toPlayer = PlayerManager::getPlayerPos() - worldPos;

	Vect turretForward = turretRot.get(MatrixRowType::ROW_2);

	Vect toPlayerNorm = toPlayer.getNorm();
	Vect tForwardNorm = turretForward.getNorm();
	Vect right = tForwardNorm.cross(Vect(0, 1, 0));

	float angle = std::acosf(toPlayerNorm.dot(tForwardNorm));

	Vect desiredMove = Vect(0, 0, 0);

	//If we need to turn, find which way to turn
	if (angle > .01f) 
	{
		if (right.dot(toPlayerNorm) < 0)
		{
			turretRot *= Matrix(RotType::ROT_Y, angle);
		}
		else
		{
			turretRot *= Matrix(RotType::ROT_Y, -angle);
		}
	}

	if (toMove) {
		if (toPlayer.mag() >= searchRange)
		{
			desiredMove += toPlayerNorm * moveMult * speed;
			submitMove = true;
		}
	}

	if (moveSide)
	{
		desiredMove += sideVect * speed;
		submitMove = true;
	}

	//After collecting movement requests in desiredMove, rotate body accordingly and move forwards
	if (submitMove)
	{
		Vect moveNorm = desiredMove.getNorm();

		Vect bodyFwdNorm = bodyRot.get(MatrixRowType::ROW_2).getNorm();

		if (!moveNorm.isEqual(bodyFwdNorm))
		{
			float turnAngle = std::acosf(moveNorm.dot(bodyFwdNorm));

			//If moveNorm and bodyFwdNorm are the same, then turnAngle returns NAN, which, if put into the world Matrix, causes the bot to disappear
			//The first if should prevent that, but JUST IN CASE, double-checking for it
			if (!isnan(turnAngle))
			{
				right = bodyFwdNorm.cross(Vect(0, 1, 0));

				if (turnAngle > maxTurnSpeed) turnAngle = maxTurnSpeed;

				if (right.dot(moveNorm) < 0)
				{
					bodyRot *= Matrix(RotType::ROT_Y, turnAngle);
				}
				else
				{
					bodyRot *= Matrix(RotType::ROT_Y, -turnAngle);
				}

				bodyPos += Vect(0, 0, 1) * bodyRot * speed;
			}
		}
	}

	float currHeight = SceneManager::getCurrentScene()->GetTerrain()->GetHeight(bodyPos.X(), bodyPos.Z());
	bodyPos.set(bodyPos.X(), currHeight, bodyPos.Z());

	float theta = GetAngle(toPlayer.mag());
	barrelRot = Matrix(ROT_X, (float)theta);

	Matrix world = bodyScale * bodyRot * Matrix(TRANS, bodyPos);
	botBody->SetWorld(world);

	UpdateCollisionData(world);
	worldPos = world.get(MatrixRowType::ROW_3);

	world = bodyScale * turretRot * Matrix(TRANS, bodyPos);
	botTurret->SetWorld(world);

	world = bodyScale * (barrelRot * turretRot) * Matrix(TRANS, bodyPos);
	botBarrel->SetWorld(world);
}

float AIBot::GetAngle(float distToPlayer)
{
	return std::atan((distToPlayer / 2) * -0.0003f);
}

void AIBot::Draw()
{
	botBody->Render(SceneManager::getCurrentScene()->getCurrentCamera());
	botTurret->Render(SceneManager::getCurrentScene()->getCurrentCamera());
	botBarrel->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

void AIBot::Collision(Bullet* other)
{
	other;
	SubmitExit();
	ParticleEffect* sparks = ParticleEffectManager::Get("Sparks");
	sparks->SpawnEmitter(Matrix(IDENTITY), bodyPos + Vect(0, 20, 0), Vect(0, 0, 0));
}

void AIBot::Collision(Building*)
{
	bodyPos.set(prevX, bodyPos.Y(), prevZ);
}

void AIBot::SceneExit()
{
	SubmitCollisionDeregistration();
	SubmitDrawDeregistration();
	SubmitUpdateDeregistration();
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_1);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_2);

	BotFactory::recycleBot(this);
}

AIBot::~AIBot()
{
	delete botBody;
	delete botTurret;
	delete botBarrel;
}
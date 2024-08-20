#include "GodCamManager.h"
#include "DragonMath.h"

GodCamManager::GodCamManager(Camera* cam)
	:godCam(cam)
{
	//For rotating camera
	SubmitInputRegistration(AZUL_KEY::KEY_I, EventType::EVENT_TYPE::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_J, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_K, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_L, EventType::KEY_HELD_DOWN);

	//For moving camera
	SubmitInputRegistration(AZUL_KEY::KEY_ARROW_UP, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_ARROW_DOWN, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_ARROW_LEFT, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_ARROW_RIGHT, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_PAGE_UP, EventType::KEY_HELD_DOWN);
	SubmitInputRegistration(AZUL_KEY::KEY_PAGE_DOWN, EventType::KEY_HELD_DOWN);

	posCam = Vect(150.0f, 150.0f, 300.0f);
	lookAtCam = Vect(0.0f, 0.0f, 0.0f);
	angle = 0;
}

void GodCamManager::KeyHeldDown(AZUL_KEY k)
{
	godCam->getRight(rightCam);

	downRot = Matrix(RotAxisAngleType::ROT_AXIS_ANGLE, rightCam, -0.05f);
	upRot = Matrix(RotAxisAngleType::ROT_AXIS_ANGLE, rightCam, 0.05f);

	Vect lookDir = lookAtCam - posCam;

	Vect left;
	Vect right;
	switch (k)
	{
	case(AZUL_KEY::KEY_I):
		lookDir = lookDir * upRot;
		lookAtCam = posCam + lookDir;
		break;
	case(AZUL_KEY::KEY_J):
		lookDir = lookDir * rightRot;
		lookAtCam = posCam + lookDir;
		angle += 0.1f;
		break;
	case(AZUL_KEY::KEY_K):
		lookDir = lookDir * downRot;
		lookAtCam = posCam + lookDir;
		break;
	case(AZUL_KEY::KEY_L):
		lookDir = lookDir * leftRot;
		lookAtCam = posCam + lookDir;
		angle -= 0.1f;
		break;
	case(AZUL_KEY::KEY_ARROW_UP):
		posCam += Vect(0, 1, 0);
		lookAtCam += Vect(0, 1, 0);
		break;
	case(AZUL_KEY::KEY_ARROW_LEFT):
		godCam->getRight(left);
		left *= -1;
		posCam += left;
		lookAtCam += left;
		break;
	case(AZUL_KEY::KEY_ARROW_DOWN):
		posCam += Vect(0, -1, 0);
		lookAtCam += Vect(0, -1, 0);
		break;
	case(AZUL_KEY::KEY_ARROW_RIGHT):
		godCam->getRight(right);
		posCam += right;
		lookAtCam += right;
		break;
	case(AZUL_KEY::KEY_PAGE_UP):
		posCam += lookDir.getNorm();
		break;
	case(AZUL_KEY::KEY_PAGE_DOWN):
		posCam -= lookDir.getNorm();
		break;
	default:
		assert(false);
	}

	godCam->setOrientAndPosition(upCam, lookAtCam, posCam);
	godCam->updateCamera();
}

GodCamManager::~GodCamManager()
{

}
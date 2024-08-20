#include "Particle.h"
#include "TimeManager.h"

Particle::Particle(Vect pos, Vect vel, Vect grav, float startAngle, float change)
	:position(pos), velocity(vel), gravity(grav), angle(startAngle), angleChange(change)
{

}

void Particle::Set(Vect pos, Vect vel, Vect grav, float startAngle, float change)
{
	position = pos;
	velocity = vel;
	gravity = grav;
	angle = startAngle;
	angleChange = change;
}

Vect Particle::GetPos()
{
	float t = TimeManager::getFrameTime();
	position += (velocity * t);
	velocity += (gravity * t);
	return position;
}

float Particle::GetAngle()
{
	angle += (angleChange * TimeManager::getFrameTime());
	return angle;
}
#ifndef _Particle
#define _Particle

#include "AzulCore.h"

class Particle
{
private:
	Vect position;
	Vect velocity;
	Vect gravity;
	float angle;
	float angleChange;

public:
	Particle() = default;
	Particle(Vect pos, Vect vel, Vect grav, float startAngle, float change);
	Particle(const Particle&) = delete;
	Particle& operator=(const Particle&) = default;
	~Particle() = default;

	void Set(Vect pos, Vect vel, Vect grav, float startAngle, float change);

	Vect GetPos();
	float GetAngle();
};

#endif _Particle
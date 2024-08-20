#ifndef _Emitter
#define _Emitter

#include <list>
#include "AzulCore.h"
#include "Drawable.h"
#include "Alarmable.h"

class Burst;
class ParticleEffect;
class Emitter : public Drawable, public Alarmable
{
private:
	std::list<Burst*> activeBursts;
	using listIt = std::list<Burst*>::iterator;

	Matrix rotation;
	Vect position;
	Vect velocity;

	ParticleEffect* parent;
	float maxBursts;
	float minBurstFrequency;
	float maxBurstFrequency;
	float frequencyRange;

public:
	Emitter();
	Emitter(ParticleEffect* e, Matrix rot, Vect pos, Vect vel);
	Emitter(const Emitter&) = delete;
	Emitter& operator=(const Emitter&) = delete;
	~Emitter();

	bool alive;

	void Draw2D() override;
	void Alarm0() override;
	void Alarm1() override;

	void Register();

	void SpawnBurst();
	void StopSpawning();

	void Set(ParticleEffect* e, Matrix rot, Vect pos, Vect vel);
	void Set(Matrix rot, Vect pos, Vect vel);
	void SetPosition(Vect newPos);
	void SetVelocity(Vect newVel);
	void SetRotation(Matrix newRot);

	void ChangeInfo(Vect offset = Vect(), Vect addVel = Vect(), Matrix multRot = Matrix(IDENTITY));
};

#endif _Emitter
#ifndef _ParticleSystemTimer
#define _ParticleSystemTimer

#include "Updateable.h"

class ParticleSystem;
class ParticleSystemTimer : public Updateable
{
private:
	ParticleSystem* p;
	float time;
	float currTime;

public:
	ParticleSystemTimer() = delete;
	ParticleSystemTimer(ParticleSystem* parent);
	ParticleSystemTimer(const ParticleSystemTimer&) = delete;
	ParticleSystemTimer& operator=(const ParticleSystemTimer&) = delete;
	~ParticleSystemTimer() = default;

	void Begin();
	void SetTimer(float t);
	void Finish();
	void Update() override;
};

#endif _ParticleSystemTimer
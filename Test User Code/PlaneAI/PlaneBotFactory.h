#ifndef _PlaneBotFactory
#define _PlaneBotFactory

#include "AzulCore.h"
#include "PlaneBotPool.h"

class PlaneBotFactory
{
private:
	static PlaneBotFactory* ptrInstance;

	PlaneBotFactory() = default;
	PlaneBotFactory(const PlaneBotFactory&) = delete;
	PlaneBotFactory& operator=(const PlaneBotFactory&) = delete;
	~PlaneBotFactory() = default;

	static PlaneBotFactory& Instance()
	{
		if (!ptrInstance) ptrInstance = new PlaneBotFactory();
		return *ptrInstance;
	}

	PlaneBotPool pool;

	void privCreatePlane(Matrix rot, Vect pos);
	void privRecyclePlane(PlaneBot* p);

public:
	static void CreatePlane(Matrix rot, Vect pos) { Instance().privCreatePlane(rot, pos); };
	static void RecyclePlane(PlaneBot* p) { Instance().privRecyclePlane(p); };
	static void Terminate();
};

#endif _PlaneBotFactory
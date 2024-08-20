#include "PlaneBotFactory.h"
#include "PlaneBot.h"

PlaneBotFactory* PlaneBotFactory::ptrInstance = nullptr;

void PlaneBotFactory::privCreatePlane(Matrix rot, Vect pos)
{
	PlaneBot* p = pool.GetPlane();
	
	p->Initialize(rot, pos);
	p->SubmitEntry();
}

void PlaneBotFactory::privRecyclePlane(PlaneBot* p)
{
	pool.ReturnPlane(p);
}

void PlaneBotFactory::Terminate()
{
	Instance().pool.Terminate();

	delete ptrInstance;
	ptrInstance = nullptr;
}
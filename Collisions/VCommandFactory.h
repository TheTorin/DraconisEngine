#ifndef _VCommandFactory
#define _VCommandFactory

#include "VCommandPool.h"

class Matrix;
class Vect;
class VCommandFactory
{
private:
	static VCommandFactory* ptrInstance;

	VCommandFactory() = default;
	VCommandFactory(const VCommandFactory&) = delete;
	VCommandFactory& operator=(const VCommandFactory&) = delete;
	~VCommandFactory() = default;

	static VCommandFactory& Instance()
	{
		if (!ptrInstance) ptrInstance = new VCommandFactory();
		return *ptrInstance;
	}

	VCommandPool pool;

	VisualizerCommand* privCreateCommandBSphere(Matrix& m, const Vect& v);
	VisualizerCommand* privCreateCommandAABB(Matrix& m, const Vect& v);
	void privRecycleCommand(VisualizerCommand* cmd);

public:
	static VisualizerCommand* CreateCommandBSphere(Matrix& m, const Vect& v) { return Instance().privCreateCommandBSphere(m, v); };
	static VisualizerCommand* CreateCommandAABB(Matrix& m, const Vect& v) { return Instance().privCreateCommandAABB(m, v); };
	static void RecycleCommand(VisualizerCommand* cmd) { Instance().privRecycleCommand(cmd); };
	static void Terminate();
};

#endif _VCommandFactory
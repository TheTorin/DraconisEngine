#include "VCommandFactory.h"
#include "VisualizerCommand.h"

VCommandFactory* VCommandFactory::ptrInstance = nullptr;

VisualizerCommand* VCommandFactory::privCreateCommandBSphere(Matrix& m, const Vect& v)
{
	VisualizerCommand* cmd = pool.getCommandBSphere();

	cmd->setFields(m, v);

	return cmd;
}

VisualizerCommand* VCommandFactory::privCreateCommandAABB(Matrix& m, const Vect& v)
{
	VisualizerCommand* cmd = pool.getCommandAABB();

	cmd->setFields(m, v);
	
	return cmd;
}

void VCommandFactory::privRecycleCommand(VisualizerCommand* cmd)
{
	pool.returnCommand(cmd);
}

void VCommandFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
#include "VCommandPool.h"
#include "VisualizerCommandBSphere.h"
#include "VisualizerCommandAABB.h"

VisualizerCommand* VCommandPool::getCommandBSphere()
{
	VisualizerCommand* cmd;

	if (recycledBSphere.empty())
	{
		cmd = new VisualizerCommandBSphere();
	}
	else
	{
		cmd = recycledBSphere.top();
		recycledBSphere.pop();
	}

	pendingCommands.push_back(cmd);
	return cmd;
}

VisualizerCommand* VCommandPool::getCommandAABB()
{
	VisualizerCommand* cmd;

	if (recycledAABB.empty())
	{
		cmd = new VisualizerCommandAABB();
	}
	else
	{
		cmd = recycledAABB.top();
		recycledAABB.pop();
	}

	pendingCommands.push_back(cmd);
	return cmd;
}

void VCommandPool::returnCommand(VisualizerCommand* cmd)
{
	if (cmd->getType() == 0)
	{
		recycledBSphere.push(cmd);
		pendingCommands.remove(cmd);
	}
	else if (cmd->getType() == 1)
	{
		recycledAABB.push(cmd);
		pendingCommands.remove(cmd);
	}
}

VCommandPool::~VCommandPool()
{
	while (!recycledBSphere.empty())
	{
		delete recycledBSphere.top();
		recycledBSphere.pop();
	}
	while (!recycledAABB.empty())
	{
		delete recycledAABB.top();
		recycledAABB.pop();
	}
	while (!pendingCommands.empty())
	{
		delete pendingCommands.front();
		pendingCommands.pop_front();
	}
}
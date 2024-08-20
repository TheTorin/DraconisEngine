#ifndef _VCommandPool
#define _VCommandPool

#include <stack>
#include <list>

class VisualizerCommand;
class VCommandPool
{
private:
	std::list<VisualizerCommand*> pendingCommands;
	std::stack<VisualizerCommand*> recycledBSphere;
	std::stack<VisualizerCommand*> recycledAABB;

public:
	VCommandPool() = default;
	VCommandPool(const VCommandPool&) = delete;
	VCommandPool& operator=(const VCommandPool&) = delete;
	~VCommandPool();

	VisualizerCommand* getCommandBSphere();
	VisualizerCommand* getCommandAABB();
	void returnCommand(VisualizerCommand*);
};

#endif _VCommandPool
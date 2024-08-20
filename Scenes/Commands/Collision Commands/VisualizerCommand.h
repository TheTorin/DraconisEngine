#ifndef _VisualizerCommand
#define _VisualizerCommand

#include "AzulCore.h"

class VisualizerCommand
{
private:

public:
	VisualizerCommand() = default;
	VisualizerCommand(const VisualizerCommand&) = delete;
	VisualizerCommand& operator=(const VisualizerCommand&) = delete;
	virtual ~VisualizerCommand() = default;

	virtual void setFields(Matrix& mat, const Vect& col) = 0;
	virtual void Execute() = 0;
	virtual int getType() = 0;
};

#endif _VisualizerCommand
#ifndef _VisualizerCommandAABB
#define _VisualizerCommandAABB

#include "VisualizerCommand.h"

class VisualizerCommandAABB : public VisualizerCommand
{
private:
	Matrix m;
	Vect v;

public:
	VisualizerCommandAABB() = default;
	VisualizerCommandAABB(const VisualizerCommandAABB&) = delete;
	VisualizerCommandAABB& operator=(const VisualizerCommandAABB&) = delete;
	~VisualizerCommandAABB() = default;

	void setFields(Matrix& mat, const Vect& col) override;
	void Execute() override;
	int getType() override { return 1; };
};

#endif _VisualizerCommandAABB
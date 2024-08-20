#ifndef _VisualizerCommandBSphere
#define _VisualizerCommandBSphere

#include "VisualizerCommand.h"

class VisualizerCommandBSphere : public VisualizerCommand
{
private:
	Matrix m;
	Vect v;

public:
	VisualizerCommandBSphere() = default;
	VisualizerCommandBSphere(const VisualizerCommandBSphere&) = delete;
	VisualizerCommandBSphere& operator=(const VisualizerCommandBSphere&) = delete;
	~VisualizerCommandBSphere() = default;

	void setFields(Matrix& mat, const Vect& col) override;
	void Execute() override;
	int getType() override { return 0; };
};

#endif _VisualizerCommandBSphere
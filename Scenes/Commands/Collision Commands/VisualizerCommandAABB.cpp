#include "VisualizerCommandAABB.h"
#include "VisualizerAttorney.h"

void VisualizerCommandAABB::setFields(Matrix& mat, const Vect& col)
{
	m = mat;
	v = col;
}

void VisualizerCommandAABB::Execute()
{
	VisualizerAttorney::Commands::renderAABB(m, v);
}
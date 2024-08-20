#include "VisualizerCommandBSphere.h"
#include "VisualizerAttorney.h"

void VisualizerCommandBSphere::setFields(Matrix& mat, const Vect& col)
{
	m = mat;
	v = col;
}

void VisualizerCommandBSphere::Execute()
{
	VisualizerAttorney::Commands::renderBSphere(m, v);
}
#include "VisualizerCommand.h"
#include "VisualizerAttorney.h"

void VisualizerCommand::setFields(Matrix& mat, const Vect& vect)
{
	m = mat;
	v = vect;
}

void VisualizerCommand::Execute()
{
	VisualizerAttorney::Commands::renderBSphere(m, v);
}
#include "GrayScaleCommand.h"

GrayScaleCommand::GrayScaleCommand() : Command("grayscale") {}

void GrayScaleCommand::execute(Image* image)
{
	if (!image)
		throw std::runtime_error("GrayScale Command: NULLPTR!");

	this->beforeState = image->createMemento();
	dynamic_cast<IGrayScale*>(image)->applyGrayscale();
}

void GrayScaleCommand::undo(Image* image)
{
	if (!image)
		throw std::runtime_error("GrayScale Command: NULLPTR!");

	image->restore(beforeState);
}

Command* GrayScaleCommand::clone() const
{
	return new GrayScaleCommand(*this);
}

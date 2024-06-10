#include "GrayScaleCommand.h"

GrayScaleCommand::GrayScaleCommand() : Command("grayscale") {}

void GrayScaleCommand::execute(Image* image)
{
	if (!image)
		throw std::runtime_error("GrayScale Command: NULLPTR!");

	this->snapshot = image;
	dynamic_cast<IGrayScale*>(image)->applyGrayscale();
}

void GrayScaleCommand::undo(Image* image)
{
	if (!image)
		throw std::runtime_error("GrayScale Command: NULLPTR!");

	image = (Image*)this->snapshot;
}

Command* GrayScaleCommand::clone() const
{
	return new GrayScaleCommand(*this);
}

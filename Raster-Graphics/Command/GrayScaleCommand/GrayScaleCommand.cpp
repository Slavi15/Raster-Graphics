#include "GrayScaleCommand.h"

GrayScaleCommand::GrayScaleCommand() : Command("grayscale") {}

void GrayScaleCommand::execute(Image* image)
{
	if (!image)
		throw std::runtime_error("GrayScale Command: NULLPTR!");

	if (image->getMagicNumber() == PPM3_IMAGE_NUMBER || image->getMagicNumber() == PPM6_IMAGE_NUMBER)
	{
		this->beforeState = image->createMemento();
		dynamic_cast<IGrayScale*>(image)->applyGrayscale();
		dynamic_cast<IGrayScale*>(image)->setGrayScaleFlag(true);
	}
}

void GrayScaleCommand::undo(Image* image)
{
	if (!image)
		throw std::runtime_error("GrayScale Command: NULLPTR!");

	if (image->getMagicNumber() == PPM3_IMAGE_NUMBER || image->getMagicNumber() == PPM6_IMAGE_NUMBER)
	{
		image->restore(beforeState);
		dynamic_cast<IGrayScale*>(image)->setGrayScaleFlag(false);
	}
}

Command* GrayScaleCommand::clone() const
{
	return new GrayScaleCommand(*this);
}

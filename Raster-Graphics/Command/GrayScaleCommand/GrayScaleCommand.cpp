#include "GrayScaleCommand.h"

GrayScaleCommand::GrayScaleCommand() : Command("grayscale") {}

void GrayScaleCommand::execute(Image* image)
{
	if (!image)
		throw std::runtime_error("GrayScale Command: NULLPTR!");

	if (image->getMagicNumber() == PPM3_IMAGE_NUMBER || image->getMagicNumber() == PPM6_IMAGE_NUMBER)
	{
		this->beforeState = image->createMemento();

		IGrayScale* grayscaleImage = dynamic_cast<IGrayScale*>(image);

		this->previousGrayScaleFlag = grayscaleImage->getGrayScaleFlag();
		grayscaleImage->applyGrayscale();
		grayscaleImage->setGrayScaleFlag(true);
	}
}

void GrayScaleCommand::undo(Image* image)
{
	if (!image)
		throw std::runtime_error("GrayScale Command: NULLPTR!");

	if (image->getMagicNumber() == PPM3_IMAGE_NUMBER || image->getMagicNumber() == PPM6_IMAGE_NUMBER)
	{
		image->restore(beforeState);
		dynamic_cast<IGrayScale*>(image)->setGrayScaleFlag(previousGrayScaleFlag);
	}
}

Command* GrayScaleCommand::clone() const
{
	return new GrayScaleCommand(*this);
}

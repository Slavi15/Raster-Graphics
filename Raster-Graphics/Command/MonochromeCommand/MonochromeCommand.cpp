#include "MonochromeCommand.h"

MonochromeCommand::MonochromeCommand() : Command("monochrome") {}

void MonochromeCommand::execute(Image* image)
{
	if (!image)
		throw std::runtime_error("Monochrome Command: NULLPTR!");

	if (image->getMagicNumber() == PBM1_IMAGE_NUMBER || image->getMagicNumber() == PBM4_IMAGE_NUMBER)
		return;

	beforeState = image->createMemento();
	dynamic_cast<IMonochrome*>(image)->applyMonochrome();
}

void MonochromeCommand::undo(Image* image)
{
	if (!image)
		throw std::runtime_error("Monochrome Command: NULLPTR!");

	if (image->getMagicNumber() == PBM1_IMAGE_NUMBER || image->getMagicNumber() == PBM4_IMAGE_NUMBER)
		return;

	image->restore(beforeState);
}

Command* MonochromeCommand::clone() const
{
	return new MonochromeCommand(*this);
}

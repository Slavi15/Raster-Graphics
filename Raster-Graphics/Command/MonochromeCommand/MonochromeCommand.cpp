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
	dynamic_cast<IMonochrome*>(image)->setMonochromeFlag(true);
}

void MonochromeCommand::undo(Image* image)
{
	if (!image)
		throw std::runtime_error("Monochrome Command: NULLPTR!");

	if (image->getMagicNumber() == PBM1_IMAGE_NUMBER || image->getMagicNumber() == PBM4_IMAGE_NUMBER)
		return;

	image->restore(beforeState);
	dynamic_cast<IMonochrome*>(image)->setMonochromeFlag(false);
}

Command* MonochromeCommand::clone() const
{
	return new MonochromeCommand(*this);
}

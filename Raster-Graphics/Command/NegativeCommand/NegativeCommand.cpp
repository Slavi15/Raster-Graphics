#include "NegativeCommand.h"

NegativeCommand::NegativeCommand() : Command("negative") {}

void NegativeCommand::execute(Image* image)
{
	if (!image)
		throw std::runtime_error("Negative Command: NULLPTR!");

	image->applyNegative();
}

void NegativeCommand::undo(Image* image)
{
	if (!image)
		throw std::runtime_error("Negative Command: NULLPTR!");

	image->applyNegative();
}

Command* NegativeCommand::clone() const
{
	return new NegativeCommand(*this);
}

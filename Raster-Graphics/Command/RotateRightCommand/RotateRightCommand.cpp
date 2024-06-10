#include "RotateRightCommand.h"

RotateRightCommand::RotateRightCommand() : Command("rotate right") {}

void RotateRightCommand::execute(Image* image)
{
	if (!image)
		throw std::runtime_error("RotateRight Command: NULLPTR!");

	image->rotateRight();
}

void RotateRightCommand::undo(Image* image)
{
	if (!image)
		throw std::runtime_error("RotateRight Command: NULLPTR!");

	image->rotateLeft();
}

Command* RotateRightCommand::clone() const
{
	return new RotateRightCommand(*this);
}

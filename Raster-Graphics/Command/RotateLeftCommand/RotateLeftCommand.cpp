#include "RotateLeftCommand.h"

RotateLeftCommand::RotateLeftCommand() : Command(CommandType::ROTATE_LEFT) {}

void RotateLeftCommand::execute(Image* image)
{
	if (!image)
		throw std::runtime_error("RotateLeft Command: NULLPTR!");

	image->rotateLeft();
}

void RotateLeftCommand::undo(Image* image)
{
	if (!image)
		throw std::runtime_error("RotateLeft Command: NULLPTR!");

	image->rotateRight();
}

Command* RotateLeftCommand::clone() const
{
	return new RotateLeftCommand(*this);
}

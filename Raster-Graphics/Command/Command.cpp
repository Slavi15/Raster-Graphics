#include "Command.h"

Command::Command(CommandType commandType) : commandType(commandType) {}

String Command::getCommand() const
{
	switch (this->commandType)
	{
	case CommandType::GRAYSCALE:
		return String("grayscale");
		break;
	case CommandType::MONOCHROME:
		return String("monochrome");
		break;
	case CommandType::NEGATIVE:
		return String("negative");
		break;
	case CommandType::ROTATE_LEFT:
		return String("rotate left");
		break;
	case CommandType::ROTATE_RIGHT:
		return String("rotate right");
		break;
	default:
		return String("none");
		break;
	}
}
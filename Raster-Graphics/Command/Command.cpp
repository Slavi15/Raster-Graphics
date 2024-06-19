#include "Command.h"

Command::Command(const String& commandType) : commandType(commandType) {}

const String& Command::getCommand() const
{
	return this->commandType;
}
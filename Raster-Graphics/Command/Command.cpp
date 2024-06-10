#include "Command.h"

Command::Command(const String& commandType) : commandType(commandType) {}

String Command::getCommand() const
{
	return this->commandType;
}
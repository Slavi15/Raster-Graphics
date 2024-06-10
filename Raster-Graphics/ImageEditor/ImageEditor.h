#pragma once

#include "../Session/SessionManager.h"

#include "../CommandFactory/FactoryOfFactories.h"

#define MAX_COMMAND_LENGTH 1024

#define NEWLINE_SEPARATOR '\n'

class ImageEditor
{
private:
	SessionManager& sessionManager = SessionManager::getInstance();

	void printCommands() const;

public:
	void runImageEditor();
};
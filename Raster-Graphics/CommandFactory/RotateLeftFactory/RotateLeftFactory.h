#pragma once

#include "../CommandFactory.h"
#include "../../Command/RotateLeftCommand/RotateLeftCommand.h"

class RotateLeftFactory : public CommandFactory
{
public:
	Command* createCommand() const override;
};
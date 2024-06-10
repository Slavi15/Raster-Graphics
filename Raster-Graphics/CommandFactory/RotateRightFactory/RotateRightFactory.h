#pragma once

#include "../CommandFactory.h"
#include "../../Command/RotateRightCommand/RotateRightCommand.h"

class RotateRightFactory : public CommandFactory
{
public:
	Command* createCommand() const override;
};
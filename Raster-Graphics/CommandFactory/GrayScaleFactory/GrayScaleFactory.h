#pragma once

#include "../CommandFactory.h"
#include "../../Command/GrayScaleCommand/GrayScaleCommand.h"

class GrayScaleFactory : public CommandFactory
{
public:
	Command* createCommand() const override;
};
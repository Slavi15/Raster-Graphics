#pragma once

#include "../CommandFactory.h"
#include "../../Command/NegativeCommand/NegativeCommand.h"

class NegativeFactory : public CommandFactory
{
public:
	Command* createCommand() const override;
};
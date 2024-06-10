#pragma once

#include "../CommandFactory.h"
#include "../../Command/MonochromeCommand/MonochromeCommand.h"

class MonochromeFactory : public CommandFactory
{
public:
	Command* createCommand() const override;
};
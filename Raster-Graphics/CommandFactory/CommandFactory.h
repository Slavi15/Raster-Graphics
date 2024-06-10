#pragma once

#include "../Command/Command.h"

class CommandFactory
{
public:
	virtual Command* createCommand() const = 0;
	virtual ~CommandFactory() noexcept = default;
};
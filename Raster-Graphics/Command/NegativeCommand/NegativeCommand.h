#pragma once

#include "../Command.h"

class NegativeCommand : public Command
{
public:
	NegativeCommand();

	void execute(Image* image) override;
	void undo(Image* image) override;

	Command* clone() const override;
};
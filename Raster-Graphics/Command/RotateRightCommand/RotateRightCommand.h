#pragma once

#include "../Command.h"

class RotateRightCommand : public Command
{
public:
	RotateRightCommand();

	void execute(Image* image) override;
	void undo(Image* image) override;

	Command* clone() const override;
};
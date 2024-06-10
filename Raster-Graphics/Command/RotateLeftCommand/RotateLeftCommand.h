#pragma once

#include "../Command.h"

class RotateLeftCommand : public Command
{
public:
	RotateLeftCommand();

	void execute(Image* image) override;
	void undo(Image* image) override;

	Command* clone() const override;
};
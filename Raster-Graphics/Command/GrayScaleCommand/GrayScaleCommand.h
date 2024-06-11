#pragma once

#include "../Command.h"
#include "../../Interface/GrayScaleInterface/IGrayScale.h"

class GrayScaleCommand : public Command
{
private:
	Memento beforeState;

public:
	GrayScaleCommand();

	void execute(Image* image) override;
	void undo(Image* image) override;

	Command* clone() const override;
};
#pragma once

#include "../Command.h"
#include "../../Interface/IGrayScale.h"

class GrayScaleCommand : public Command
{
private:
	Image* snapshot;

public:
	GrayScaleCommand();

	void execute(Image* image) override;
	void undo(Image* image) override;

	Command* clone() const override;
};
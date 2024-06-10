#pragma once

#include "../Command.h"
#include "../../Interface/IMonochrome.h"

class MonochromeCommand : public Command
{
private:
	Image* snapshot;

public:
	MonochromeCommand();

	void execute(Image* image) override;
	void undo(Image* image) override;

	Command* clone() const override;
};
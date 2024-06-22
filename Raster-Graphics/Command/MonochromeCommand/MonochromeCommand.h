#pragma once

#include "../Command.h"
#include "../../Interface/MonochromeInterface/IMonochrome.h"

class MonochromeCommand : public Command
{
private:
	Memento beforeState;
	bool previousMonochromeFlag = false;

public:
	MonochromeCommand();

	void execute(Image* image) override;
	void undo(Image* image) override;

	Command* clone() const override;
};
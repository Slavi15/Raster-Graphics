#pragma once

#include "../Image/Image.h"

class Command
{
private:
	String commandType;

public:
	Command(const String& commandType);

	String getCommand() const;

	virtual void execute(Image* image) = 0;
	virtual void undo(Image* image) = 0;

	virtual Command* clone() const = 0;

	virtual ~Command() noexcept = default;
};
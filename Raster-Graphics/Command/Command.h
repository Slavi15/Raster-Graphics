#pragma once

#include "../Image/Image.h"

enum class CommandType : char
{
	NONE,
	GRAYSCALE,
	MONOCHROME,
	NEGATIVE,
	ROTATE_LEFT,
	ROTATE_RIGHT
};

class Command
{
private:
	CommandType commandType = CommandType::NONE;

public:
	Command(CommandType commandType);
	
	String getCommand() const;

	virtual void execute(Image* image) = 0;
	virtual void undo(Image* image) = 0;

	virtual Command* clone() const = 0;

	virtual ~Command() noexcept = default;
};
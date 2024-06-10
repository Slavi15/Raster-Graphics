#include "RotateLeftFactory.h"

Command* RotateLeftFactory::createCommand() const
{
	return new RotateLeftCommand();
}

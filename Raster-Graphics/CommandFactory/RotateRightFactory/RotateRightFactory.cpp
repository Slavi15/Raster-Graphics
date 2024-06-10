#include "RotateRightFactory.h"

Command* RotateRightFactory::createCommand() const
{
    return new RotateRightCommand();
}

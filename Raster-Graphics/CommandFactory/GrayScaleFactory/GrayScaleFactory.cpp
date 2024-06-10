#include "GrayScaleFactory.h"

Command* GrayScaleFactory::createCommand() const
{
    return new GrayScaleCommand();
}

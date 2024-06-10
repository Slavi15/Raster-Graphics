#include "MonochromeFactory.h"

Command* MonochromeFactory::createCommand() const
{
    return new MonochromeCommand();
}

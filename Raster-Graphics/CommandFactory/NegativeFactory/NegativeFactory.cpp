#include "NegativeFactory.h"

Command* NegativeFactory::createCommand() const
{
    return new NegativeCommand();
}

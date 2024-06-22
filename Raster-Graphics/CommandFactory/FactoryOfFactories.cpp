#include "FactoryOfFactories.h"

CommandFactory* FactoryOfFactories::factoryOfFactories(CommandType commandType)
{
    if (commandType == CommandType::GRAYSCALE)
    {
        return new GrayScaleFactory();
    }
    else if (commandType == CommandType::MONOCHROME)
    {
        return new MonochromeFactory();
    }
    else if (commandType == CommandType::NEGATIVE)
    {
        return new NegativeFactory();
    }
    else if (commandType == CommandType::ROTATE_LEFT)
    {
        return new RotateLeftFactory();
    }
    else if (commandType == CommandType::ROTATE_RIGHT)
    {
        return new RotateRightFactory();
    }

    return nullptr;
}

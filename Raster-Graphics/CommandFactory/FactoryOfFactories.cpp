#include "FactoryOfFactories.h"

CommandFactory* FactoryOfFactories::factoryOfFactories(const String& command)
{
    if (command == "grayscale")
    {
        return new GrayScaleFactory();
    }
    else if (command == "monochrome")
    {
        return new MonochromeFactory();
    }
    else if (command == "negative")
    {
        return new NegativeFactory();
    }
    else if (command == "rotate left")
    {
        return new RotateLeftFactory();
    }
    else if (command == "rotate right")
    {
        return new RotateRightFactory();
    }

    return nullptr;
}

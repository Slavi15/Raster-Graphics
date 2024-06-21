#include "IMonochrome.h"

IMonochrome::IMonochrome(const String& fileName) : Image(fileName) {}

bool IMonochrome::getMonochromeFlag() const
{
    return this->isMonochromeFlag;
}

void IMonochrome::setMonochromeFlag(bool isMonochromeFlag)
{
    this->isMonochromeFlag = isMonochromeFlag;
}

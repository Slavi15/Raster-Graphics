#include "IGrayScale.h"

IGrayScale::IGrayScale(const String& fileName) : Image(fileName) {}

bool IGrayScale::getGrayScaleFlag() const
{
	return this->isGrayScaleFlag;
}

void IGrayScale::setGrayScaleFlag(bool isGrayScaleFlag)
{
	this->isGrayScaleFlag = isGrayScaleFlag;
}

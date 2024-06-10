#pragma once

#include "CommandFactory.h"

#include "GrayScaleFactory/GrayScaleFactory.h"
#include "MonochromeFactory/MonochromeFactory.h"
#include "NegativeFactory/NegativeFactory.h"
#include "RotateLeftFactory/RotateLeftFactory.h"
#include "RotateRightFactory/RotateRightFactory.h"

class FactoryOfFactories
{
public:
	static CommandFactory* factoryOfFactories(const String& command);
};
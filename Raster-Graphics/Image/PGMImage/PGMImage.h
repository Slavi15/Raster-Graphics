#pragma once

#include "../../Interface/IGrayScale.h"
#include "../../Interface/IMonochrome.h"

#include "../../Vector/Vector.hpp"

class PGMImage : public IGrayScale, public IMonochrome
{
public:
	PGMImage(const String& fileName);
};
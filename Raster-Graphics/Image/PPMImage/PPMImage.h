#pragma once

#include "../../Interface/IGrayScale.h"
#include "../../Interface/IMonochrome.h"

#include "../../Vector/Vector.hpp"
#include "../../Pixel/Pixel.hpp"

class PPMImage : public IGrayScale, public IMonochrome
{
public:
	PPMImage(const String& fileName);
};
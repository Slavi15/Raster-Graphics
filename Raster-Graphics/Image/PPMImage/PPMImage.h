#pragma once

#include "../../Interface/IGrayScale.h"
#include "../../Interface/IMonochrome.h"

#include "../../DataStructures/Vector.hpp"
#include "../../Pixel/Pixel.hpp"

class PPMImage : public IGrayScale, public IMonochrome
{
protected:
	static constexpr uint16_t minimalPPMColor = 0;

public:
	PPMImage(const String& fileName);
};
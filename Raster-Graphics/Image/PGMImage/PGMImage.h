#pragma once

#include "../../Interface/IMonochrome.h"
#include "../../Vector/Vector.hpp"

class PGMImage : public IMonochrome
{
protected:
	static constexpr uint16_t minimalPGMColor = 0;

public:
	PGMImage(const String& fileName);
};
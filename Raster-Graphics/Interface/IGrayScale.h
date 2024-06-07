#pragma once

#include "../Image/Image.h"

class IGrayScale : virtual public Image
{
public:
	IGrayScale(const String& fileName);

	virtual void applyGrayscale() = 0;

	virtual ~IGrayScale() noexcept = default;
};
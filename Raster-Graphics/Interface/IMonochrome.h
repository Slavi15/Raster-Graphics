#pragma once

#include "../Image/Image.h"

class IMonochrome : virtual public Image
{
public:
	IMonochrome(const String& fileName);

	virtual void applyMonochrome() = 0;
	virtual bool isMonochrome() const = 0;

	virtual ~IMonochrome() noexcept = default;
};
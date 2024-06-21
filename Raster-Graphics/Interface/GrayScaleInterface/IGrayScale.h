#pragma once

#include "../../Image/Image.h"

class IGrayScale : virtual public Image
{
private:
	bool isGrayScaleFlag = false;

public:
	IGrayScale(const String& fileName);

	bool getGrayScaleFlag() const;
	void setGrayScaleFlag(bool isGrayScaleFlag);

	virtual void applyGrayscale() = 0;
	virtual bool isGrayScale() const = 0;

	virtual ~IGrayScale() noexcept = default;
};
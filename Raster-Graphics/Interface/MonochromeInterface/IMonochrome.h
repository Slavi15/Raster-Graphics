#pragma once

#include "../../Image/Image.h"

class IMonochrome : virtual public Image
{
private:
	bool isMonochromeFlag = false;

public:
	IMonochrome(const String& fileName);

	bool getMonochromeFlag() const;
	void setMonochromeFlag(bool isMonochromeFlag);

	virtual void applyMonochrome() = 0;
	virtual bool isMonochrome() const = 0;

	virtual ~IMonochrome() noexcept = default;
};
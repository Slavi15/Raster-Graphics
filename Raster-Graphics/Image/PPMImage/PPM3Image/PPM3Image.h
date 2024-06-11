#pragma once

#include "../PPMImage.h"

class PPM3Image : public PPMImage
{
public:
	PPM3Image(const String& fileName);

	void load() override;

	void save() const override;
	void saveAs(const String& fileName) const override;

	Image* clone() const override;
};
#pragma once

#include "../PPMImage.h"

class PPM6Image : public PPMImage
{
public:
	PPM6Image(const String& fileName);

	void load() override;

	void save() const override;
	void saveAs(const String& fileName) const override;

	Image* clone() const override;
};
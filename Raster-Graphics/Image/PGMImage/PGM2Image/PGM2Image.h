#pragma once

#include "../PGMImage.h"

class PGM2Image : public PGMImage
{
public:
	PGM2Image(const String& fileName);

	void load() override;

	void save() const override;
	void saveAs(const String& fileName) const override;

	Image* clone() const override;
};
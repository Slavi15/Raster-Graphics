#pragma once

#include "PBMImage.h"

class PBM1Image : public PBMImage
{
public:
	PBM1Image(const String& fileName);

	void load() override;

	void save() const override;
	void saveAs(const String& fileName) const override;

	Image* clone() const override;
};
#pragma once

#include "PBMImage.h"

class PBM4Image : public PBMImage
{
public:
	PBM4Image(const String& fileName);

	void load() override;
	void save(const String& fileName) const override;

	Image* clone() const override;
};
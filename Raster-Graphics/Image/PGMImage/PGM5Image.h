#pragma once

#include "PGMImage.h"

class PGM5Image : public PGMImage
{
public:
	PGM5Image(const String& fileName);

	void load() override;

	void save() const override;
	void saveAs(const String& fileName) const override;

	Image* clone() const override;
};
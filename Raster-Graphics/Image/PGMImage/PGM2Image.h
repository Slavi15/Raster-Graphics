#pragma once

#include "PGMImage.h"

class PGM2Image : public PGMImage
{
private:
	Vector<uint16_t> imageData;

public:
	PGM2Image(const String& fileName);

	void load() override;
	void save(const String& fileName) const override;

	void applyGrayscale() override;
	void applyMonochrome() override;
	void applyNegative() override;

	void rotateLeft() override;
	void rotateRight() override;

	Image* clone() const override;
};
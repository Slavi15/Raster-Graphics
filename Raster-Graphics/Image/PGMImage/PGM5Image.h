#pragma once

#include "PGMImage.h"

class PGM5Image : public PGMImage
{
private:
	Vector<uint8_t> imageData;

public:
	PGM5Image(const String& fileName);

	void load() override;
	void save(const String& fileName) const override;

	void applyGrayscale() override;
	void applyMonochrome() override;
	void applyNegative() override;

	void rotateLeft() override;
	void rotateRight() override;

	Image* clone() const override;
};
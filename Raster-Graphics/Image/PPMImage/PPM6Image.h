#pragma once

#include "PPMImage.h"

class PPM6Image : public PPMImage
{
private:
	Vector<Pixel<uint8_t>> imageData;

public:
	PPM6Image(const String& fileName);

	void load() override;
	void save(const String& fileName) const override;

	void applyGrayscale() override;
	void applyMonochrome() override;
	void applyNegative() override;

	void rotateLeft() override;
	void rotateRight() override;

	Image* clone() const override;
};
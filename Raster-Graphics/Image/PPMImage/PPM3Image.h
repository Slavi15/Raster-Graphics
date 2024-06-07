#pragma once

#include "PPMImage.h"

class PPM3Image : public PPMImage
{
private:
	Vector<Pixel<uint16_t>> imageData;

public:
	PPM3Image(const String& fileName);

	void load() override;
	void save(const String& fileName) const override;

	void applyGrayscale() override;
	void applyMonochrome() override;
	void applyNegative() override;

	void rotateLeft() override;
	void rotateRight() override;

	Image* clone() const override;
};
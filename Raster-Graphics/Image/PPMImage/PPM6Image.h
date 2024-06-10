#pragma once

#include "PPMImage.h"

class PPM6Image : public PPMImage
{
private:
	Vector<Pixel<uint8_t>> imageData;

public:
	PPM6Image(const String& fileName);

	void load() override;
	void reset() override;

	void save() const override;
	void saveAs(const String& fileName) const override;

	void applyGrayscale() override;
	bool isGrayScale() const override;

	void applyMonochrome() override;
	bool isMonochrome() const override;

	void applyNegative() override;

	void rotateLeft() override;
	void rotateRight() override;

	Image* clone() const override;
};
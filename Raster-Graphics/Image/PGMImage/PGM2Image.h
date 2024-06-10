#pragma once

#include "PGMImage.h"

class PGM2Image : public PGMImage
{
private:
	Vector<uint16_t> imageData;

public:
	PGM2Image(const String& fileName);

	void load() override;
	void reset() override;

	void save() const override;
	void saveAs(const String& fileName) const override;

	void applyMonochrome() override;
	bool isMonochrome() const override;

	void applyNegative() override;

	void rotateLeft() override;
	void rotateRight() override;

	Image* clone() const override;
};
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

	void applyMonochrome() override;
	bool isMonochrome() const override;

	void applyNegative() override;

	void rotateLeft() override;
	void rotateRight() override;

	Image* clone() const override;
};
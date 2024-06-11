#pragma once

#include "../../Interface/IMonochrome.h"
#include "../../DataStructures/Vector.hpp"

#define MINIMAL_PGM_COLOR 0

class PGMImage : public IMonochrome
{
protected:
	Vector<uint8_t> imageData;

public:
	PGMImage(const String& fileName);

	void applyMonochrome() override;
	bool isMonochrome() const override;

	void applyNegative() override;

	void rotateLeft() override;
	void rotateRight() override;
};
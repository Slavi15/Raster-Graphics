#pragma once

#include "../Image.h"
#include "../../DataStructures/BitSet.h"

class PBMImage : public Image
{
protected:
	BitSet imageData;

public:
	PBMImage(const String& fileName);

	void reset() override;

	void applyNegative() override;

	void rotateLeft() override;
	void rotateRight() override;
};
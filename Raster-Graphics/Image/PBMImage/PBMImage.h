#pragma once

#include "../Image.h"
#include "../../DataStructures/BitSet.h"

class PBMImage : public Image
{
protected:
	BitSet imageData;

public:
	PBMImage(const String& fileName);

	void applyNegative() override;

	void rotateLeft() override;
	void rotateRight() override;

	void collage(Image* leftImage, Image* rightImage, const String& direction) override;
	void horizontalCollage(Image* leftImage, Image* rightImage) override;
	void verticalCollage(Image* leftImage, Image* rightImage) override;

	Memento createMemento() const override;
	void restore(const Memento& memento) override;
};
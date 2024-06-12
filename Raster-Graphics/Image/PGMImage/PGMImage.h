#pragma once

#include "../../Interface/MonochromeInterface/IMonochrome.h"
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

	void collage(Image* leftImage, Image* rightImage, const String& direction) override;
	void horizontalCollage(Image* leftImage, Image* rightImage) override;
	void verticalCollage(Image* leftImage, Image* rightImage) override;

	Memento createMemento() const override;
	void restore(const Memento& memento) override;
};
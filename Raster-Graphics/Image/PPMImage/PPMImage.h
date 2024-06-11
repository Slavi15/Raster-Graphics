#pragma once

#include "../../Interface/GrayScaleInterface/IGrayScale.h"
#include "../../Interface/MonochromeInterface/IMonochrome.h"

#include "../../DataStructures/Vector.hpp"
#include "../../Pixel/Pixel.h"

#define MINIMAL_PPM_COLOR 0

class PPMImage : public IGrayScale, public IMonochrome
{
protected:
	Vector<Pixel> imageData;

public:
	PPMImage(const String& fileName);

	void applyGrayscale() override;
	bool isGrayScale() const override;

	void applyMonochrome() override;
	bool isMonochrome() const override;

	void applyNegative() override;

	void rotateLeft() override;
	void rotateRight() override;

	Memento createMemento() const override;
	void restore(const Memento& memento) override;
};
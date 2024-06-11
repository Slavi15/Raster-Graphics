#include "PPMImage.h"

PPMImage::PPMImage(const String& fileName) : IGrayScale(fileName), IMonochrome(fileName) {}

void PPMImage::applyGrayscale()
{
	if (isGrayScale())
		throw std::logic_error("PPM6 Image: Image is already grayscale!");

	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		if (!this->imageData[i].isGrayScale())
		{
			this->imageData[i].RGBToGrayScale();
		}
	}
}

bool PPMImage::isGrayScale() const
{
	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		if (!this->imageData[i].isGrayScale())
		{
			return false;
		}
	}

	return true;
}

void PPMImage::applyMonochrome()
{
	if (isMonochrome())
		throw std::logic_error("PPM6 Image: Image is already monochrome!");

	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		this->imageData[i].RGBToGrayScale();

		if (this->imageData[i].getR() > getMaxNumber() / 2)
		{
			this->imageData[i].RGBToMonochrome(getMaxNumber());
		}
		else
		{
			this->imageData[i].RGBToMonochrome(MINIMAL_PPM_COLOR);
		}
	}
}

bool PPMImage::isMonochrome() const
{
	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		bool grayScaleCheck = this->imageData[i].isGrayScale();

		if (!grayScaleCheck || (grayScaleCheck && (this->imageData[i].getR() != getMaxNumber() && this->imageData[i].getR() != MINIMAL_PPM_COLOR)))
		{
			return false;
		}
	}

	return true;
}

void PPMImage::applyNegative()
{
	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		this->imageData[i].RGBToNegative(getMaxNumber());
	}
}

void PPMImage::rotateLeft()
{
	Vector<Pixel> newImageData(this->imageData.getSize());

	for (size_t i = 0; i < getHeight(); i++)
	{
		for (size_t j = 0; j < getWidth(); j++)
		{
			newImageData[(getWidth() - j - 1) * getHeight() + i] = this->imageData[i * getWidth() + j];
		}
	}

	std::swap(this->width, this->height);
	this->imageData = newImageData;
}

void PPMImage::rotateRight()
{
	Vector<Pixel> newImageData(this->imageData.getSize());

	for (size_t i = 0; i < getHeight(); i++)
	{
		for (size_t j = 0; j < getWidth(); j++)
		{
			newImageData[(getHeight() - i - 1) + getHeight() * j] = this->imageData[i * getWidth() + j];
		}
	}

	std::swap(this->width, this->height);
	this->imageData = newImageData;
}

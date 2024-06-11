#include "PBMImage.h"

PBMImage::PBMImage(const String& fileName) : Image(fileName) {}

void PBMImage::applyNegative()
{
	for (size_t i = 0; i < this->imageData.getN(); i++)
	{
		this->imageData.invert(i);
	}
}

void PBMImage::rotateLeft()
{
	BitSet newImageData(getWidth() * getHeight());

	for (size_t i = 0; i < getHeight(); i++)
	{
		for (size_t j = 0; j < getWidth(); j++)
		{
			if (this->imageData.contains(i * getWidth() + j))
			{
				newImageData.add((getWidth() - j - 1) * getHeight() + i);
			}
		}
	}

	std::swap(this->width, this->height);
	this->imageData = newImageData;
}

void PBMImage::rotateRight()
{
	BitSet newImageData(getWidth() * getHeight());

	for (size_t i = 0; i < getHeight(); i++)
	{
		for (size_t j = 0; j < getWidth(); j++)
		{
			if (this->imageData.contains(i * getWidth() + j))
			{
				newImageData.add((getHeight() - i - 1) + getHeight() * j);
			}
		}
	}

	std::swap(this->width, this->height);
	this->imageData = newImageData;
}

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

void PBMImage::collage(Image* leftImage, Image* rightImage, const String& direction)
{
	if (!leftImage || !rightImage)
		throw std::runtime_error("PPM Image Collage: NULLPTR!");

	if (direction == "horizontal")
	{
		return horizontalCollage(leftImage, rightImage);
	}
	else if (direction == "vertical")
	{
		return verticalCollage(leftImage, rightImage);
	}
}

void PBMImage::horizontalCollage(Image* leftImage, Image* rightImage)
{
	if (!leftImage || !rightImage)
		throw std::runtime_error("PPM Image Collage: NULLPTR!");

	uint16_t newWidth = std::max(leftImage->getWidth(), rightImage->getWidth());
	uint16_t newHeight = leftImage->getHeight() + rightImage->getHeight();

	resize(newWidth, newHeight);

	this->imageData = BitSet(newWidth * newHeight);

	for (size_t i = 0; i < leftImage->getHeight(); i++)
	{
		for (size_t j = 0; j < leftImage->getWidth(); j++)
		{
			if (dynamic_cast<PBMImage*>(leftImage)->imageData.contains(i * leftImage->getWidth() + j))
			{
				this->imageData.add(i * newWidth + j);
			}
		}
	}

	for (size_t i = 0; i < rightImage->getHeight(); i++)
	{
		for (size_t j = 0; j < rightImage->getWidth(); j++)
		{
			if (dynamic_cast<PBMImage*>(rightImage)->imageData.contains(i * rightImage->getWidth() + j))
			{
				this->imageData.add((i + leftImage->getHeight()) * newWidth + j);
			}
		}
	}

	std::cout << "New collage \"" << getFileName() << "\" created" << std::endl;
	save();
}

void PBMImage::verticalCollage(Image* leftImage, Image* rightImage)
{
	if (!leftImage || !rightImage)
		throw std::runtime_error("PPM Image Collage: NULLPTR!");

	uint16_t newWidth = leftImage->getWidth() + rightImage->getWidth();
	uint16_t newHeight = std::max(leftImage->getHeight(), rightImage->getHeight());

	resize(newWidth, newHeight);

	this->imageData = BitSet(newWidth * newHeight);

	for (size_t i = 0; i < leftImage->getHeight(); i++)
	{
		for (size_t j = 0; j < leftImage->getWidth(); j++)
		{
			if (dynamic_cast<PBMImage*>(leftImage)->imageData.contains(i * leftImage->getWidth() + j))
			{
				this->imageData.add(i * newWidth + j);
			}
		}

		for (size_t j = 0; j < rightImage->getWidth(); j++)
		{
			if (dynamic_cast<PBMImage*>(rightImage)->imageData.contains(i * rightImage->getWidth() + j))
			{
				this->imageData.add(i * newWidth + j + leftImage->getWidth());
			}
		}
	}

	std::cout << "New collage \"" << getFileName() << "\" created" << std::endl;
	save();
}

Memento PBMImage::createMemento() const
{
	return Memento(this->clone());
}

void PBMImage::restore(const Memento& memento)
{
	this->imageData = dynamic_cast<PBMImage*>(memento.getState())->imageData;
}

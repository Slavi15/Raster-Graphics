#include "PGMImage.h"

PGMImage::PGMImage(const String& fileName) : IMonochrome(fileName), Image(fileName) {}

void PGMImage::applyMonochrome()
{
	if (getMonochromeFlag() || isMonochrome())
		throw std::logic_error("PGMImage: Image is already monochrome!");

	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		if (this->imageData[i] > getMaxNumber() / 2)
		{
			this->imageData[i] = getMaxNumber();
		}
		else
		{
			this->imageData[i] = MINIMAL_PGM_COLOR;
		}
	}
}

bool PGMImage::isMonochrome() const
{
	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		if (this->imageData[i] != 0 && this->imageData[i] != getMaxNumber())
		{
			return false;
		}
	}

	return true;
}

void PGMImage::applyNegative()
{
	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		this->imageData[i] = getMaxNumber() - this->imageData[i];
	}
}

void PGMImage::rotateLeft()
{
	Vector<uint8_t> newImageData(this->imageData.getSize());

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

void PGMImage::rotateRight()
{
	Vector<uint8_t> newImageData(this->imageData.getSize());

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

void PGMImage::collage(Image* leftImage, Image* rightImage, const String& direction)
{
	if (!leftImage || !rightImage)
		throw std::runtime_error("PPM Image Collage: NULLPTR!");

	this->maxNumber = std::max(leftImage->getMaxNumber(), rightImage->getMaxNumber());

	if (direction == "horizontal")
	{
		return horizontalCollage(leftImage, rightImage);
	}
	else if (direction == "vertical")
	{
		return verticalCollage(leftImage, rightImage);
	}
}

void PGMImage::horizontalCollage(Image* leftImage, Image* rightImage)
{
	if (!leftImage || !rightImage)
		throw std::runtime_error("PPM Image Collage: NULLPTR!");

	uint16_t newWidth = std::max(leftImage->getWidth(), rightImage->getWidth());
	uint16_t newHeight = leftImage->getHeight() + rightImage->getHeight();

	resize(newWidth, newHeight);

	if (getMagicNumber() == PGM2_IMAGE_NUMBER)
	{
		this->imageData = Vector<uint8_t>(newWidth * newHeight);
	}
	else if (getMagicNumber() == PGM5_IMAGE_NUMBER)
	{
		this->imageData = Vector<uint8_t>(leftImage->getImageSize(leftImage->getFileName()) + rightImage->getImageSize(rightImage->getFileName()));
	}

	for (size_t i = 0; i < leftImage->getHeight(); i++)
	{
		for (size_t j = 0; j < leftImage->getWidth(); j++)
		{
			this->imageData[i * newWidth + j] = dynamic_cast<PGMImage*>(leftImage)->imageData[i * leftImage->getWidth() + j];
		}
	}

	for (size_t i = 0; i < rightImage->getHeight(); i++)
	{
		for (size_t j = 0; j < rightImage->getWidth(); j++)
		{
			this->imageData[(i + leftImage->getHeight()) * newWidth + j] = dynamic_cast<PGMImage*>(rightImage)->imageData[i * rightImage->getWidth() + j];
		}
	}

	std::cout << "New collage \"" << getFileName() << "\" created" << std::endl;
	save();
}

void PGMImage::verticalCollage(Image* leftImage, Image* rightImage)
{
	if (!leftImage || !rightImage)
		throw std::runtime_error("PPM Image Collage: NULLPTR!");

	uint16_t newWidth = leftImage->getWidth() + rightImage->getWidth();
	uint16_t newHeight = std::max(leftImage->getHeight(), rightImage->getHeight());

	resize(newWidth, newHeight);

	if (getMagicNumber() == PGM2_IMAGE_NUMBER)
	{
		this->imageData = Vector<uint8_t>(newWidth * newHeight);
	}
	else if (getMagicNumber() == PGM5_IMAGE_NUMBER)
	{
		this->imageData = Vector<uint8_t>(leftImage->getImageSize(leftImage->getFileName()) + rightImage->getImageSize(rightImage->getFileName()));
	}

	for (size_t i = 0; i < leftImage->getHeight(); i++)
	{
		for (size_t j = 0; j < leftImage->getWidth(); j++)
		{
			this->imageData[i * newWidth + j] = dynamic_cast<PGMImage*>(leftImage)->imageData[i * leftImage->getWidth() + j];
		}

		for (size_t j = 0; j < rightImage->getWidth(); j++)
		{
			this->imageData[i * newWidth + (j + leftImage->getWidth())] = dynamic_cast<PGMImage*>(rightImage)->imageData[i * rightImage->getWidth() + j];
		}
	}

	std::cout << "New collage \"" << getFileName() << "\" created" << std::endl;
	save();
}

Memento PGMImage::createMemento() const
{
	return Memento(this->clone());
}

void PGMImage::restore(const Memento& memento)
{
	this->imageData = dynamic_cast<PGMImage*>(memento.getState())->imageData;
}

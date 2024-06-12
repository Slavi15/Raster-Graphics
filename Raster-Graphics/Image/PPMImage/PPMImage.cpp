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

void PPMImage::collage(Image* leftImage, Image* rightImage, const String& direction)
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

void PPMImage::horizontalCollage(Image* leftImage, Image* rightImage)
{
	if (!leftImage || !rightImage)
		throw std::runtime_error("PPM Image Collage: NULLPTR!");

	uint16_t newWidth = std::max(leftImage->getWidth(), rightImage->getWidth());
	uint16_t newHeight = leftImage->getHeight() + rightImage->getHeight();

	resize(newWidth, newHeight);

	if (getMagicNumber() == PPM3_IMAGE_NUMBER)
	{
		this->imageData = Vector<Pixel>(newWidth * newHeight);
	}
	else if (getMagicNumber() == PPM6_IMAGE_NUMBER)
	{
		this->imageData = Vector<Pixel>(leftImage->getImageSize(leftImage->getFileName()) + rightImage->getImageSize(rightImage->getFileName()));
	}

	for (size_t i = 0; i < leftImage->getHeight(); i++)
	{
		for (size_t j = 0; j < leftImage->getWidth(); j++)
		{
			this->imageData[i * newWidth + j] = dynamic_cast<PPMImage*>(leftImage)->imageData[i * leftImage->getWidth() + j];
		}
	}

	for (size_t i = 0; i < rightImage->getHeight(); i++)
	{
		for (size_t j = 0; j < rightImage->getWidth(); j++)
		{
			this->imageData[(i + leftImage->getHeight()) * newWidth + j] = dynamic_cast<PPMImage*>(rightImage)->imageData[i * rightImage->getWidth() + j];
		}
	}

	std::cout << "New collage \"" << getFileName() << "\" created" << std::endl;
	save();
}

void PPMImage::verticalCollage(Image* leftImage, Image* rightImage)
{
	if (!leftImage || !rightImage)
		throw std::runtime_error("PPM Image Collage: NULLPTR!");

	uint16_t newWidth = leftImage->getWidth() + rightImage->getWidth();
	uint16_t newHeight = std::max(leftImage->getHeight(), rightImage->getHeight());

	resize(newWidth, newHeight);

	if (getMagicNumber() == PPM3_IMAGE_NUMBER)
	{
		this->imageData = Vector<Pixel>(newWidth * newHeight);
	}
	else if (getMagicNumber() == PPM6_IMAGE_NUMBER)
	{
		this->imageData = Vector<Pixel>(leftImage->getImageSize(leftImage->getFileName()) + rightImage->getImageSize(rightImage->getFileName()));
	}

	for (size_t i = 0; i < leftImage->getHeight(); i++)
	{
		for (size_t j = 0; j < leftImage->getWidth(); j++)
		{
			this->imageData[i * newWidth + j] = dynamic_cast<PPMImage*>(leftImage)->imageData[i * leftImage->getWidth() + j];
		}

		for (size_t j = 0; j < rightImage->getWidth(); j++)
		{
			this->imageData[i * newWidth + j + leftImage->getWidth()] = dynamic_cast<PPMImage*>(rightImage)->imageData[i * rightImage->getWidth() + j];
		}
	}

	std::cout << "New collage \"" << getFileName() << "\" created" << std::endl;
	save();
}

Memento PPMImage::createMemento() const
{
	return Memento(this->clone());
}

void PPMImage::restore(const Memento& memento)
{
	this->imageData = dynamic_cast<PPMImage*>(memento.getState())->imageData;
}

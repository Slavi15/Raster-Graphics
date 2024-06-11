#include "PGMImage.h"

PGMImage::PGMImage(const String& fileName) : IMonochrome(fileName), Image(fileName) {}

void PGMImage::applyMonochrome()
{
	if (isMonochrome())
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

Memento PGMImage::createMemento() const
{
	return Memento(this->clone());
}

void PGMImage::restore(const Memento& memento)
{
	this->imageData = dynamic_cast<PGMImage*>(memento.getState())->imageData;
}

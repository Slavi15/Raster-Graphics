#include "PGM5Image.h"

PGM5Image::PGM5Image(const String& fileName) : PGMImage(fileName), Image(fileName) {}

void PGM5Image::load()
{
	std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary);

	if (!ifs.is_open())
		throw std::runtime_error("PGM5 Image: Could not open file!");

	//ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	ifs.ignore();
	ifs >> this->magicNumber >> this->width >> this->height >> this->maxNumber;

	size_t imageSize = getImageSize(ifs);

	this->imageData = Vector<uint8_t>(imageSize);
	ifs.read(reinterpret_cast<char*>(&this->imageData[0]), imageSize * sizeof(uint8_t));

	ifs.close();
}

void PGM5Image::save(const String& fileName) const
{
	std::ofstream ofs(fileName.c_str(), std::ios::out | std::ios::binary);

	if (!ofs.is_open())
		throw std::runtime_error("PGM5 Image: Could not open file!");

	ofs << "P5" << std::endl;
	ofs << this->width << " " << this->height << std::endl;
	ofs << this->maxNumber;

	ofs.write(reinterpret_cast<const char*>(&this->imageData[0]), this->imageData.getSize() * sizeof(uint8_t));

	ofs.close();
}

void PGM5Image::applyMonochrome()
{
	if (isMonochrome())
		throw std::logic_error("PGM5Image: Image is already monochrome!");

	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		if (this->imageData[i] > getMaxNumber() / 2)
		{
			this->imageData[i] = getMaxNumber();
		}
		else
		{
			this->imageData[i] = minimalPGMColor;
		}
	}
}

bool PGM5Image::isMonochrome() const
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

void PGM5Image::applyNegative()
{
	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		this->imageData[i] = getMaxNumber() - this->imageData[i];
	}
}

void PGM5Image::rotateLeft()
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

void PGM5Image::rotateRight()
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

Image* PGM5Image::clone() const
{
	return new PGM5Image(*this);
}

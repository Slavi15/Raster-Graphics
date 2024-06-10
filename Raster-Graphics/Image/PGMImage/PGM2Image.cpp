#include "PGM2Image.h"

PGM2Image::PGM2Image(const String& fileName) : PGMImage(fileName), Image(fileName) {}

void PGM2Image::load()
{
	std::ifstream ifs(fileName.c_str(), std::ios::in);

	if (!ifs.is_open())
		throw std::runtime_error("PGM2 Image: Could not open file!");

	//ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	ifs.ignore();
	ifs >> this->magicNumber >> this->width >> this->height >> this->maxNumber;

	this->imageData = Vector<uint16_t>(getWidth() * getHeight());

	size_t index = 0;
	while (!ifs.eof())
	{
		uint16_t num;
		ifs >> num;
		imageData[index++] = num;
	}

	ifs.close();
}

void PGM2Image::reset()
{
	this->imageData.clear();
}

void PGM2Image::save() const
{
	saveAs(this->fileName);
}

void PGM2Image::saveAs(const String& fileName) const
{
	std::ofstream ofs(fileName.c_str(), std::ios::out);

	if (!ofs.is_open())
		throw std::runtime_error("PGM2 Image: Could not open file!");

	ofs << "P2" << std::endl;
	ofs << this->width << " " << this->height << std::endl;
	ofs << this->maxNumber << std::endl;

	size_t vectorIndex = 0;
	for (size_t i = 0; i < getHeight(); i++)
	{
		for (size_t j = 0; j < getWidth(); j++)
		{
			ofs << imageData[vectorIndex++] << " ";
		}

		ofs << std::endl;
	}

	ofs.close();
}

void PGM2Image::applyMonochrome()
{
	if (isMonochrome())
		throw std::logic_error("PGM2Image: Image is already monochrome!");

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

bool PGM2Image::isMonochrome() const
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

void PGM2Image::applyNegative()
{
	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		this->imageData[i] = getMaxNumber() - this->imageData[i];
	}
}

void PGM2Image::rotateLeft()
{
	Vector<uint16_t> newImageData(this->imageData.getSize());

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

void PGM2Image::rotateRight()
{
	Vector<uint16_t> newImageData(this->imageData.getSize());

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

Image* PGM2Image::clone() const
{
	return new PGM2Image(*this);
}

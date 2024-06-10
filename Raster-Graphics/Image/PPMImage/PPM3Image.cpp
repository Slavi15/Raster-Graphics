#include "PPM3Image.h"

PPM3Image::PPM3Image(const String& fileName) : PPMImage(fileName), Image(fileName) {}

void PPM3Image::load()
{
	std::ifstream ifs(fileName.c_str(), std::ios::in);

	if (!ifs.is_open())
		throw std::runtime_error("PPM3 Image: Could not open file!");

	ifs.ignore();
	ifs >> this->magicNumber >> this->width >> this->height >> this->maxNumber;

	this->imageData = Vector<Pixel<uint16_t>>(getWidth() * getHeight());

	size_t index = 0;
	while (!ifs.eof())
	{
		Pixel<uint16_t> pixel;
		ifs >> pixel;
		imageData[index++] = pixel;
	}

	ifs.close();
}

void PPM3Image::reset()
{
	this->imageData.clear();
}

void PPM3Image::save() const
{
	saveAs(this->fileName);
}

void PPM3Image::saveAs(const String& fileName) const
{
	std::ofstream ofs(fileName.c_str(), std::ios::out);

	if (!ofs.is_open())
		throw std::runtime_error("PPM3 Image: Could not open file!");

	ofs << "P3" << std::endl;
	ofs << this->width << " " << this->height << std::endl;
	ofs << this->maxNumber << std::endl;

	for (size_t i = 0; i < imageData.getSize(); i++)
	{
		ofs << imageData[i];
	}

	ofs.close();
}

void PPM3Image::applyGrayscale()
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

bool PPM3Image::isGrayScale() const
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

void PPM3Image::applyMonochrome()
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
			this->imageData[i].RGBToMonochrome(minimalPPMColor);
		}
	}
}

bool PPM3Image::isMonochrome() const
{
	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		bool grayScaleCheck = this->imageData[i].isGrayScale();

		if (!grayScaleCheck || (grayScaleCheck && (this->imageData[i].getR() != getMaxNumber() && this->imageData[i].getR() != minimalPPMColor)))
		{
			return false;
		}
	}

	return true;
}

void PPM3Image::applyNegative()
{
	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		this->imageData[i].RGBToNegative(getMaxNumber());
	}
}

void PPM3Image::rotateLeft()
{
	Vector<Pixel<uint16_t>> newImageData(this->imageData.getSize());

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

void PPM3Image::rotateRight()
{
	Vector<Pixel<uint16_t>> newImageData(this->imageData.getSize());

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

Image* PPM3Image::clone() const
{
	return new PPM3Image(*this);
}

#include "PPM6Image.h"

PPM6Image::PPM6Image(const String& fileName) : PPMImage(fileName), Image(fileName) {}

void PPM6Image::load()
{
	std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary);

	if (!ifs.is_open())
		throw std::runtime_error("PPM6 Image: Could not open file!");

	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	ifs >> this->width >> this->height >> this->maxNumber;

	size_t imageSize = getImageSize(ifs);
	size_t numPixels = (imageSize % sizeof(Pixel<uint8_t>) == 0) ? imageSize / sizeof(Pixel<uint8_t>) : (imageSize / sizeof(Pixel<uint8_t>)) + 1;

	this->imageData = Vector<Pixel<uint8_t>>(numPixels);
	ifs.read(reinterpret_cast<char*>(&this->imageData[0]), numPixels * sizeof(Pixel<uint8_t>));

	ifs.close();
}

void PPM6Image::save(const String& fileName) const
{
	std::ofstream ofs(fileName.c_str(), std::ios::out | std::ios::binary);

	if (!ofs.is_open())
		throw std::runtime_error("PPM6 Image: Could not open file!");

	ofs << "P6" << std::endl;
	ofs << this->width << " " << this->height << std::endl;
	ofs << this->maxNumber;

	ofs.write(reinterpret_cast<const char*>(&this->imageData[0]), this->imageData.getSize() * sizeof(Pixel<uint8_t>));

	ofs.close();
}

void PPM6Image::applyGrayscale()
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

bool PPM6Image::isGrayScale() const
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

void PPM6Image::applyMonochrome()
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

bool PPM6Image::isMonochrome() const
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

void PPM6Image::applyNegative()
{
	for (size_t i = 0; i < this->imageData.getSize(); i++)
	{
		this->imageData[i].RGBToNegative(getMaxNumber());
	}
}

void PPM6Image::rotateLeft()
{
	Vector<Pixel<uint8_t>> newImageData(this->imageData.getSize());

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

void PPM6Image::rotateRight()
{
	Vector<Pixel<uint8_t>> newImageData(this->imageData.getSize());

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

Image* PPM6Image::clone() const
{
	return new PPM6Image(*this);
}

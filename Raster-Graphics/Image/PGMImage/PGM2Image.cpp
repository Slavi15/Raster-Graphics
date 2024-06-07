#include "PGM2Image.h"

PGM2Image::PGM2Image(const String& fileName) : PGMImage(fileName), Image(fileName) {}

void PGM2Image::load()
{
	std::ifstream ifs(fileName.c_str(), std::ios::in);

	if (!ifs.is_open())
		throw std::runtime_error("PGM2 Image: Could not open file!");

	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	ifs >> this->width >> this->height >> this->maxNumber;

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

void PGM2Image::save(const String& fileName) const
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

void PGM2Image::applyGrayscale()
{

}

void PGM2Image::applyMonochrome()
{

}

void PGM2Image::applyNegative()
{

}

void PGM2Image::rotateLeft()
{

}

void PGM2Image::rotateRight()
{

}

Image* PGM2Image::clone() const
{
	return new PGM2Image(*this);
}

#include "PGM5Image.h"

PGM5Image::PGM5Image(const String& fileName) : PGMImage(fileName), Image(fileName) {}

void PGM5Image::load()
{
	std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary);

	if (!ifs.is_open())
		throw std::runtime_error("PGM5 Image: Could not open file!");

	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	ifs >> this->width >> this->height >> this->maxNumber;

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

void PGM5Image::applyGrayscale()
{

}

void PGM5Image::applyMonochrome()
{

}

void PGM5Image::applyNegative()
{

}

void PGM5Image::rotateLeft()
{

}

void PGM5Image::rotateRight()
{

}

Image* PGM5Image::clone() const
{
	return new PGM5Image(*this);
}

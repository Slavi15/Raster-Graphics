#include "PBM4Image.h"

PBM4Image::PBM4Image(const String& fileName) : PBMImage(fileName)
{
	this->magicNumber = PBM4_IMAGE_NUMBER;
}

void PBM4Image::load()
{
	std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary);

	if (!ifs.is_open())
		throw std::runtime_error("PBM4 Image: Could not open file!");

	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	ifs >> this->width >> this->height >> this->maxNumber;

	size_t imageSize = getWidth() * getHeight();

	this->imageData = BitSet(imageSize);
	this->imageData.readBinaryRaw(ifs);

	ifs.close();
}

void PBM4Image::save() const
{
	saveAs(this->fileName);
}

void PBM4Image::saveAs(const String& fileName) const
{
	std::ofstream ofs(fileName.c_str(), std::ios::out | std::ios::binary);

	if (!ofs.is_open())
		throw std::runtime_error("PBM4 Image: Could not open file!");

	ofs << "P4" << std::endl;
	ofs << this->width << " " << this->height;

	this->imageData.writeBinaryRaw(ofs);

	ofs.close();
}

Image* PBM4Image::clone() const
{
	return new PBM4Image(*this);
}

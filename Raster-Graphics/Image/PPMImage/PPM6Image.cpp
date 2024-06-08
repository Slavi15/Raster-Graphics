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

}

bool PPM6Image::isGrayScale() const
{
	return false;
}

void PPM6Image::applyMonochrome()
{

}

bool PPM6Image::isMonochrome() const
{
	return false;
}

void PPM6Image::applyNegative()
{

}

void PPM6Image::rotateLeft()
{

}

void PPM6Image::rotateRight()
{

}

Image* PPM6Image::clone() const
{
	return new PPM6Image(*this);
}

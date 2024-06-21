#include "PPM6Image.h"

PPM6Image::PPM6Image(const String& fileName) : PPMImage(fileName), Image(fileName)
{
	this->magicNumber = PPM6_IMAGE_NUMBER;
}

void PPM6Image::load()
{
	std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary);

	if (!ifs.is_open())
		throw std::runtime_error("PPM6 Image: Could not open file!");

	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	ifs >> this->width >> this->height >> this->maxNumber;

	size_t imageSize = getImageSize(ifs);
	size_t numPixels = (imageSize % sizeof(Pixel) == 0) ? imageSize / sizeof(Pixel) : (imageSize / sizeof(Pixel)) + 1;

	this->imageData = Vector<Pixel>(numPixels);
	ifs.read(reinterpret_cast<char*>(&this->imageData[0]), numPixels * sizeof(Pixel));

	ifs.close();
}

void PPM6Image::save() const
{
	saveAs(this->fileName);
}

void PPM6Image::saveAs(const String& fileName) const
{
	std::ofstream ofs(fileName.c_str(), std::ios::out | std::ios::binary);

	if (!ofs.is_open())
		throw std::runtime_error("PPM6 Image: Could not open file!");

	ofs << "P6" << std::endl;
	ofs << this->width << " " << this->height << std::endl;
	ofs << this->maxNumber << std::endl;

	ofs.write(reinterpret_cast<const char*>(&this->imageData[0]), this->imageData.getSize() * sizeof(Pixel));

	ofs.close();
}

Image* PPM6Image::clone() const
{
	return new PPM6Image(*this);
}

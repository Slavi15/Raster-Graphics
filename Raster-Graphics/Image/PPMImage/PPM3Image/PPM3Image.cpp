#include "PPM3Image.h"

PPM3Image::PPM3Image(const String& fileName) : PPMImage(fileName), Image(fileName)
{
	this->magicNumber = PPM3_IMAGE_NUMBER;
}

void PPM3Image::load()
{
	std::ifstream ifs(fileName.c_str(), std::ios::in);

	if (!ifs.is_open())
		throw std::runtime_error("PPM3 Image: Could not open file!");

	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	ifs >> this->width >> this->height >> this->maxNumber;

	this->imageData = Vector<Pixel>(getWidth() * getHeight());

	size_t index = 0;
	while (!ifs.eof())
	{
		Pixel pixel;
		ifs >> pixel;
		imageData[index++] = pixel;
	}

	ifs.close();
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
	ofs << this->maxNumber;

	for (size_t i = 0; i < imageData.getSize(); i++)
	{
		ofs << imageData[i];
	}

	ofs.close();
}

Image* PPM3Image::clone() const
{
	return new PPM3Image(*this);
}

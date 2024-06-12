#include "PBM1Image.h"

PBM1Image::PBM1Image(const String& fileName) : PBMImage(fileName)
{
	this->magicNumber = PBM1_IMAGE_NUMBER;
}

void PBM1Image::load()
{
	std::ifstream ifs(fileName.c_str(), std::ios::in);

	if (!ifs.is_open())
		throw std::runtime_error("PBM1 Image: Could not open file!");

	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	ifs >> this->width >> this->height >> this->maxNumber;

	this->imageData = BitSet(getWidth() * getHeight());

	size_t index = 0;
	while (!ifs.eof())
	{
		bool num;
		ifs >> num;

		if (num)
			imageData.add(index);

		index++;
	}

	ifs.close();
}

void PBM1Image::save() const
{
	saveAs(this->fileName);
}

void PBM1Image::saveAs(const String& fileName) const
{
	std::ofstream ofs(fileName.c_str(), std::ios::out);

	if (!ofs.is_open())
		throw std::runtime_error("PBM1 Image: Could not open file!");

	ofs << "P1" << std::endl;
	ofs << this->width << " " << this->height;

	size_t num = 0;
	for (size_t i = 0; i < getHeight(); i++)
	{
		for (size_t j = 0; j < getWidth(); j++)
		{
			ofs << imageData.contains(num) << " ";
			num++;
		}

		ofs << std::endl;
	}

	ofs.close();
}

Image* PBM1Image::clone() const
{
	return new PBM1Image(*this);
}

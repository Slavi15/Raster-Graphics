#include "Image.h"

Image::Image(const String& fileName) : fileName(fileName) {}

const char* Image::getFileName() const
{
    return fileName.c_str();
}

uint8_t Image::getMagicNumber() const
{
    return this->magicNumber;
}

size_t Image::getWidth() const
{
    return this->width;
}

size_t Image::getHeight() const
{
    return this->height;
}

uint16_t Image::getMaxNumber() const
{
    return this->maxNumber;
}

size_t Image::getImageSize(std::ifstream& ifs)
{
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);

    size_t size = ifs.tellg();
    ifs.seekg(currentPos, std::ios::beg);

    return size - currentPos;
}

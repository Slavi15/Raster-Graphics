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

void Image::resize(size_t newWidth, size_t newHeight)
{
    this->width = newWidth;
    this->height = newHeight;
}

size_t Image::getImageSize(std::ifstream& ifs)
{
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);

    size_t size = ifs.tellg();
    ifs.seekg(currentPos, std::ios::beg);

    return size - currentPos;
}

size_t Image::getImageSize(const char* fileName)
{
    std::ifstream ifs(fileName, std::ios::in | std::ios::binary);

    if (!ifs.is_open())
        throw std::runtime_error("NULLPTR!");

    return getImageSize(ifs);
}

#include "ImageFactory.h"

Image* ImageFactory::imageFactory(const char* fileName)
{
    if (!fileName)
        throw std::runtime_error("Image Factory: NULLPTR!");

    FilePath filePath(fileName);

    std::ifstream ifs(fileName, std::ios::in);

    if (!ifs.is_open())
        throw std::runtime_error("Image Factory: Error opening file!");

    ifs.ignore();
    uint8_t magicNumber = ifs.get();

    if (filePath.getExtension() == ".pbm")
    {
        return PBMImageFactory(fileName, magicNumber);
    }
    else if (filePath.getExtension() == ".pgm")
    {
        return PGMImageFactory(fileName, magicNumber);
    }
    else if (filePath.getExtension() == ".ppm")
    {
        return PPMImageFactory(fileName, magicNumber);
    }

    return nullptr;
}

Image* ImageFactory::imageFactory(const char* fileName, uint8_t magicNumber)
{
    if (magicNumber == PBM1_IMAGE_NUMBER)
    {
        return new PBM1Image(fileName);
    }
    else if (magicNumber == PBM4_IMAGE_NUMBER)
    {
        return new PBM4Image(fileName);
    }
    else if (magicNumber == PGM2_IMAGE_NUMBER)
    {
        return new PGM2Image(fileName);
    }
    else if (magicNumber == PGM5_IMAGE_NUMBER)
    {
        return new PGM5Image(fileName);
    }
    else if (magicNumber == PPM3_IMAGE_NUMBER)
    {
        return new PPM3Image(fileName);
    }
    else if (magicNumber == PPM6_IMAGE_NUMBER)
    {
        return new PPM6Image(fileName);
    }

    return nullptr;
}

Image* ImageFactory::PBMImageFactory(const char* fileName, uint8_t magicNumber)
{
    if (magicNumber == PBM1_IMAGE_NUMBER)
    {
        return new PBM1Image(fileName);
    }
    else if (magicNumber == PBM4_IMAGE_NUMBER)
    {
        return new PBM4Image(fileName);
    }

    return nullptr;
}

Image* ImageFactory::PGMImageFactory(const char* fileName, uint8_t magicNumber)
{
    if (magicNumber == PGM2_IMAGE_NUMBER)
    {
        return new PGM2Image(fileName);
    }
    else if (magicNumber == PGM5_IMAGE_NUMBER)
    {
        return new PGM5Image(fileName);
    }

    return nullptr;
}

Image* ImageFactory::PPMImageFactory(const char* fileName, uint8_t magicNumber)
{
    if (magicNumber == PPM3_IMAGE_NUMBER)
    {
        return new PPM3Image(fileName);
    }
    else if (magicNumber == PPM6_IMAGE_NUMBER)
    {
        return new PPM6Image(fileName);
    }

    return nullptr;
}

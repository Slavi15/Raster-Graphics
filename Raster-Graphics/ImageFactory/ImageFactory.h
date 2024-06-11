#pragma once

#include "../Image/Image.h"
#include "../../FilePath/FilePath.h"

#include "../Image/PBMImage/PBM1Image/PBM1Image.h"
#include "../Image/PBMImage/PBM4Image/PBM4Image.h"

#include "../Image/PGMImage/PGM2Image/PGM2Image.h"
#include "../Image/PGMImage/PGM5Image/PGM5Image.h"

#include "../Image/PPMImage/PPM3Image/PPM3Image.h"
#include "../Image/PPMImage/PPM6Image/PPM6Image.h"

class ImageFactory
{
public:
	static Image* imageFactory(const char* fileName);
};
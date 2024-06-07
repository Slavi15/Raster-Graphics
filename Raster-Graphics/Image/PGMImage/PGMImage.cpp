#include "PGMImage.h"

PGMImage::PGMImage(const String& fileName) : IGrayScale(fileName), IMonochrome(fileName) {}
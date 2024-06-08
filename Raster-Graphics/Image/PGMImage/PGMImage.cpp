#include "PGMImage.h"

PGMImage::PGMImage(const String& fileName) : IMonochrome(fileName), Image(fileName) {}
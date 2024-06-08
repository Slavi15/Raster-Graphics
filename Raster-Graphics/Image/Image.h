#pragma once

#include <fstream>
#include <sstream>

#include "../String/String.h"
#include "../FilePath/FilePath.h"

#define MAX_BUFFER_LENGTH 1024

class Image
{
protected:
	String fileName;
	uint8_t magicNumber = 0;
	uint16_t width = 0;
	uint16_t height = 0;
	uint16_t maxNumber = 0;

	static size_t getImageSize(std::ifstream& ifs);

public:
	Image(const String& fileName);

	virtual size_t getWidth() const;
	virtual size_t getHeight() const;
	virtual uint16_t getMaxNumber() const;

	virtual void load() = 0;
	virtual void save(const String& filePath) const = 0;

	virtual void applyNegative() = 0;
	virtual void rotateLeft() = 0;
	virtual void rotateRight() = 0;

	virtual Image* clone() const = 0;

	virtual ~Image() noexcept = default;
};
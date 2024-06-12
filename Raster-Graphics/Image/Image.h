#pragma once

#include <fstream>
#include <sstream>

#include "../String/String.h"
#include "../FilePath/FilePath.h"

#include "../Memento/Memento.h"

#define PBM1_IMAGE_NUMBER '1'
#define PBM4_IMAGE_NUMBER '4'

#define PGM2_IMAGE_NUMBER '2'
#define PGM5_IMAGE_NUMBER '5'

#define PPM3_IMAGE_NUMBER '3'
#define PPM6_IMAGE_NUMBER '6'

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
	static size_t getImageSize(const char* fileName);

public:
	Image(const String& fileName);

	const char* getFileName() const;
	uint8_t getMagicNumber() const;
	size_t getWidth() const;
	size_t getHeight() const;
	uint16_t getMaxNumber() const;

	virtual void load() = 0;

	virtual void save() const = 0;
	virtual void saveAs(const String& filePath) const = 0;

	virtual void applyNegative() = 0;
	virtual void rotateLeft() = 0;
	virtual void rotateRight() = 0;

	virtual void collage(Image* leftImage, Image* rightImage, const String& direction) = 0;
	virtual void horizontalCollage(Image* leftImage, Image* rightImage) = 0;
	virtual void verticalCollage(Image* leftImage, Image* rightImage) = 0;

	void resize(size_t newWidth, size_t newHeight);

	virtual Memento createMemento() const = 0;
	virtual void restore(const Memento& memento) = 0;

	virtual Image* clone() const = 0;

	virtual ~Image() noexcept = default;
};
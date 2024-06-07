#include "FilePath.h"

FilePath::FilePath(const String& fileName)
{
	const char* start = fileName.c_str();
	const char* end = fileName.c_str() + fileName.getSize();

	const char* iterator = end;

	while (iterator != start && *iterator != '.')
	{
		iterator--;
	}

	this->fileName = fileName.substr(0, iterator - start);
	this->fileExtension = fileName.substr(iterator - start, end - iterator);
}

const String& FilePath::getFileName() const
{
	return this->fileName;
}

const String& FilePath::getExtension() const
{
	return this->fileExtension;
}

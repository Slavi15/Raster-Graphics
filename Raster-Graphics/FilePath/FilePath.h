#pragma once

#include "../String/String.h"

class FilePath
{
private:
	String fileName;
	String fileExtension;

public:
	FilePath(const String& fileName);

	const String& getFileName() const;
	const String& getExtension() const;
};
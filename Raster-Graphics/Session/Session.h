#pragma once

#include "../Image/Image.h"
#include "../Command/Command.h"

#include "../ImageFactory/ImageFactory.h"

#include "../DataStructures/Vector.hpp"
#include "../SmartPointers/PolymorphicPtr.hpp"

class Session
{
private:
	size_t sessionID = 0;
	static size_t sessionCounter;

	size_t commandsIndex = 0;

	Vector<PolymorphicPtr<Image>> images;
	Vector<PolymorphicPtr<Command>> commands;

public:
	Session();

	size_t getSessionID() const;
	int getImageIndex(const String& fileName) const;

	void addImage(Image* image);
	void addCommand(Command* command);

	void removeImage();

	void execute();
	void executeAll();

	void undo();

	void createCollage(const String& direction, const String& leftImage, const String& rightImage, const String& outputFile);

	void save();
	void saveAs(const String& fileName);

	Session* clone() const;

	void printSession() const;
};
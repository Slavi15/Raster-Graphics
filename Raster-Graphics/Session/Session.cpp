#include "Session.h"

size_t Session::sessionCounter = 0;

Session::Session() : sessionID(++sessionCounter) {}

size_t Session::getSessionID() const
{
	return this->sessionID;
}

int Session::getImageIndex(const String& fileName) const
{
	for (size_t i = 0; i < this->images.getSize(); i++)
	{
		if (this->images[i]->getFileName() == fileName)
		{
			return i;
		}
	}

	return -1;
}

void Session::addImage(Image* image)
{
	if (!image)
		throw std::runtime_error("Session: NULLPTR!");

	this->images.push_back(image);
	std::cout << "Image \"" << image->getFileName() << "\" added" << std::endl;
}

void Session::addCommand(Command* command)
{
	if (!command)
		throw std::runtime_error("Session: NULLPTR!");

	this->commands.push_back(command);
}

void Session::removeImage()
{
	this->images.pop_back();
}

void Session::execute()
{
	if (this->commands.isEmpty())
		return;

	for (size_t i = 0; i < this->images.getSize(); i++)
	{
		try
		{
			this->commands[commandsCount]->execute(this->images[i].get());
		}
		catch (const std::logic_error&) { continue; }
		catch (const std::invalid_argument&) { continue; }
		catch (const std::runtime_error&) { return; }
	}

	commandsCount++;
}

void Session::executeAll()
{
	if (this->commands.isEmpty())
		return;

	for (size_t i = commandsCount; i < this->commands.getSize(); i++)
	{
		execute();
	}
}

void Session::undo()
{
	if (this->commands.isEmpty())
		throw std::runtime_error("Session: No commands are available in history!");

	for (size_t i = 0; i < this->images.getSize(); i++)
	{
		this->commands[this->commands.getSize() - 1]->undo(this->images[i].get());
	}

	this->commands.pop_back();
	commandsCount--;
}

void Session::createCollage(const String& direction, const String& leftImage, const String& rightImage, const String& outputFile)
{
	int leftImageIndex = getImageIndex(leftImage);
	int rightImageIndex = getImageIndex(rightImage);

	FilePath filePathOne(leftImage);
	FilePath filePathTwo(rightImage);

	if (filePathOne.getExtension() != filePathTwo.getExtension())
	{
		std::cout << "Cannot make a collage from different types! ( " << filePathOne.getExtension() << " and " << filePathTwo.getExtension() << ")" << std::endl;
		return;
	}

	if (this->images[leftImageIndex]->getWidth() != this->images[rightImageIndex]->getWidth() ||
		this->images[leftImageIndex]->getHeight() != this->images[rightImageIndex]->getHeight())
	{
		std::cout << "Cannot make a collage from images with different dimensions!" << std::endl;
		return;
	}

	Image* output = ImageFactory::imageFactory(outputFile.c_str(), this->images[leftImageIndex]->getMagicNumber());

	output->collage(this->images[leftImageIndex].get(), this->images[rightImageIndex].get(), direction);

	delete output;
}

void Session::save()
{
	executeAll();

	for (size_t i = 0; i < this->images.getSize(); i++)
	{
		this->images[i]->save();
	}
}

void Session::saveAs(const String& fileName)
{
	executeAll();

	this->images[0]->saveAs(fileName);
}

Session* Session::clone() const
{
	return new Session(*this);
}

void Session::printSession() const
{
	std::cout << "Name of images in the session: ";

	for (size_t i = 0; i < this->images.getSize(); i++)
	{
		std::cout << this->images[i]->getFileName() << " ";
	}

	std::cout << std::endl;
	std::cout << "Pending transformations: ";

	for (size_t i = 0; i < this->commands.getSize(); i++)
	{
		if (i != this->commands.getSize() - 1)
		{
			std::cout << this->commands[i]->getCommand() << ", ";
		}
		else
		{
			std::cout << this->commands[i]->getCommand();
		}
	}

	std::cout << std::endl;
}

#include "Session.h"

size_t Session::sessionCounter = 0;

Session::Session() : sessionID(++sessionCounter) {}

size_t Session::getSessionID() const
{
	return this->sessionID;
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
		throw std::runtime_error("Session: No commands are available!");

	for (size_t i = 0; i < this->images.getSize(); i++)
	{
		try
		{
			this->commands[commandsIndex]->execute(this->images[i].get());
		}
		catch (const std::logic_error&) { continue; }
		catch (const std::invalid_argument&) { continue; }
		catch (const std::runtime_error&) { return; }
	}

	(++commandsIndex) %= this->commands.getSize();
}

void Session::executeAll()
{
	if (this->commands.isEmpty())
		throw std::runtime_error("Session: No commands are available!");

	for (size_t i = 0; i < this->commands.getSize(); i++)
	{
		execute();
	}
}

void Session::undo()
{
	if (this->commandsIndex < 0)
		throw std::runtime_error("Session: No commands are available in history!");

	for (size_t i = 0; i < this->images.getSize(); i++)
	{
		this->commands[commandsIndex]->undo(this->images[i].get());
	}

	(--commandsIndex) %= this->commands.getSize();
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

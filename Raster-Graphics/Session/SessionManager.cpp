#include "SessionManager.h"

SessionManager::SessionManager() = default;

SessionManager& SessionManager::getInstance()
{
	static SessionManager instance;
	return instance;
}

void SessionManager::loadSession(const char* fileNames)
{
	if (!fileNames)
		throw std::runtime_error("Session Manager: NULLPTR!");

	Session* currentSession = new Session();

	std::cout << "Session with ID: " << this->sessions[currentSessionIndex]->getSessionID() << " started" << std::endl;

	std::stringstream ss(fileNames);
	char fileName[MAX_FILENAME_LENGTH + 1]{ };

	while (!ss.eof())
	{
		ss.getline(fileName, MAX_FILENAME_LENGTH + 1, SPACE_SEPARATOR);

		Image* image = ImageFactory::imageFactory(fileName);
		image->load();

		currentSession->addImage(image);
	}

	this->sessions.push_back(currentSession);
	currentSessionIndex++;
}

void SessionManager::addImageToCurrentSession(const char* fileNames)
{
	if (!fileNames)
		throw std::runtime_error("Session Manager: NULLPTR!");

	std::stringstream ss(fileNames);
	char fileName[MAX_FILENAME_LENGTH + 1]{ };

	while (!ss.eof())
	{
		ss.getline(fileName, MAX_FILENAME_LENGTH + 1, SPACE_SEPARATOR);

		Image* image = ImageFactory::imageFactory(fileName);
		image->load();

		this->sessions[currentSessionIndex]->addImage(image);
	}

	// only for one file
	//this->sessions[currentSessionIndex]->addImage(ImageFactory::imageFactory(fileName));
}

void SessionManager::closeImageCurrentSession()
{
	this->sessions[currentSessionIndex]->removeImage();
}

void SessionManager::addCommandCurrentSession(Command* cmd)
{
	if (!cmd)
		throw std::runtime_error("Session Manager: NULLPTR!");

	this->sessions[currentSessionIndex]->addCommand(cmd);
}

void SessionManager::executeCommandCurrentSession()
{
	this->sessions[currentSessionIndex]->execute();
}

void SessionManager::executeAllCommandsCurrentSession()
{
	this->sessions[currentSessionIndex]->executeAll();
}

void SessionManager::undoCommandCurrentSession()
{
	this->sessions[currentSessionIndex]->undo();
}

void SessionManager::saveCurrentSession()
{
	this->sessions[currentSessionIndex]->save();
}

void SessionManager::saveAsCurrentSession(const char* fileName)
{
	if (!fileName)
		throw std::runtime_error("Session Manager: NULLPTR!");

	this->sessions[currentSessionIndex]->saveAs(fileName);
}

void SessionManager::switchSession(size_t newIndex)
{
	if (newIndex >= this->sessions.getSize())
		throw std::out_of_range("Session Manager: Invalid index!");

	currentSessionIndex = newIndex - 1;
	std::cout << "You switched to session with ID: " << this->sessions[currentSessionIndex]->getSessionID() << "!" << std::endl;
	this->sessions[currentSessionIndex]->printSession();
}

void SessionManager::printCurrentSessionInfo() const
{
	this->sessions[currentSessionIndex]->printSession();
}

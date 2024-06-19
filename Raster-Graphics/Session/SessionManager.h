#pragma once

#include "Session.h"

#include "../Command/Command.h"

#include "../DataStructures/Vector.hpp"
#include "../SmartPointers/PolymorphicPtr.hpp"

#define MAX_FILENAME_LENGTH 1024
#define SPACE_SEPARATOR ' '

class SessionManager
{
private:
	Vector<PolymorphicPtr<Session>> sessions;
	int currentSessionIndex = -1;

	SessionManager();

public:
	static SessionManager& getInstance();

	SessionManager(const SessionManager& other) = delete;
	SessionManager& operator=(const SessionManager& other) = delete;

	void loadSession(const char* fileNames);

	void addImageToCurrentSession(const char* fileNames);
	void closeImageCurrentSession();

	void addCommandCurrentSession(Command* cmd);

	void executeCommandCurrentSession();
	void executeAllCommandsCurrentSession();

	void undoCommandCurrentSession();

	void createCollage(const String& direction, const String& leftImage, const String& rightImage, const String& outputFile);

	void saveCurrentSession();
	void saveAsCurrentSession(const char* fileName);

	void switchSession(size_t newIndex);

	void printCurrentSessionInfo() const;

	~SessionManager() noexcept = default;
};
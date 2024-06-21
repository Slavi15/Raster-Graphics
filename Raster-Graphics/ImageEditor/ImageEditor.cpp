#include "ImageEditor.h"

void ImageEditor::runImageEditor()
{
	char command[MAX_COMMAND_LENGTH + 1]{ };

	std::cout << "> ";

	CommandFactory* commandFactory = nullptr;

	while (std::cin.getline(command, MAX_COMMAND_LENGTH + 1, NEWLINE_SEPARATOR))
	{
		std::stringstream ss(command);

		char buffer[MAX_COMMAND_LENGTH + 1]{ };
		ss.getline(buffer, MAX_COMMAND_LENGTH + 1, SPACE_SEPARATOR);

		if (strcmp(buffer, "load") == 0)
		{
			ss.getline(buffer, MAX_COMMAND_LENGTH + 1, NEWLINE_SEPARATOR);
			sessionManager.loadSession(buffer);
		}
		else if (strcmp(buffer, "add") == 0)
		{
			ss.getline(buffer, MAX_COMMAND_LENGTH + 1, NEWLINE_SEPARATOR);
			sessionManager.addImageToCurrentSession(buffer);
		}
		else if (strcmp(buffer, "close") == 0)
		{
			sessionManager.closeImageCurrentSession();
		}
		else if (strcmp(buffer, "grayscale") == 0)
		{
			commandFactory = FactoryOfFactories::factoryOfFactories("grayscale");
			sessionManager.addCommandCurrentSession(commandFactory->createCommand());
			delete commandFactory;
		}
		else if (strcmp(buffer, "monochrome") == 0)
		{
			commandFactory = FactoryOfFactories::factoryOfFactories("monochrome");
			sessionManager.addCommandCurrentSession(commandFactory->createCommand());
			delete commandFactory;
		}
		else if (strcmp(buffer, "negative") == 0)
		{
			commandFactory = FactoryOfFactories::factoryOfFactories("negative");
			sessionManager.addCommandCurrentSession(commandFactory->createCommand());
			delete commandFactory;
		}
		else if (strcmp(buffer, "rotate") == 0)
		{
			ss.getline(buffer, MAX_COMMAND_LENGTH + 1, NEWLINE_SEPARATOR);

			if (strcmp(buffer, "left") == 0)
			{
				commandFactory = FactoryOfFactories::factoryOfFactories("rotate left");
				sessionManager.addCommandCurrentSession(commandFactory->createCommand());
				delete commandFactory;
			}
			else if (strcmp(buffer, "right") == 0)
			{
				commandFactory = FactoryOfFactories::factoryOfFactories("rotate right");
				sessionManager.addCommandCurrentSession(commandFactory->createCommand());
				delete commandFactory;
			}
		}
		else if (strcmp(buffer, "undo") == 0)
		{
			sessionManager.undoCommandCurrentSession();
		}
		else if (strcmp(buffer, "session") == 0 && strcmp(command, "session info") == 0)
		{
			sessionManager.printCurrentSessionInfo();
		}
		else if (strcmp(buffer, "switch") == 0)
		{
			size_t index;
			ss >> index;

			try
			{
				sessionManager.switchSession(index);
			}
			catch (const std::out_of_range& exc)
			{
				std::cout << "Error: " << exc.what() << std::endl;
			}
		}
		else if (strcmp(buffer, "collage") == 0)
		{
			String direction, leftImage, rightImage, outputImage;
			ss >> direction >> leftImage >> rightImage >> outputImage;

			sessionManager.createCollage(direction, leftImage, rightImage, outputImage);
		}
		else if (strcmp(buffer, "save") == 0)
		{
			sessionManager.saveCurrentSession();
		}
		else if (strcmp(buffer, "saveAs") == 0)
		{
			ss.getline(buffer, MAX_COMMAND_LENGTH + 1, NEWLINE_SEPARATOR);
			sessionManager.saveAsCurrentSession(buffer);
		}
		else if (strcmp(buffer, "help") == 0)
		{
			printCommands();
		}
		else if (strcmp(buffer, "exit") == 0)
		{
			return;
		}
		else
		{
			std::cout << "Invalid command! Please, try again!" << std::endl;
		}

		std::cout << "> ";
	}
}

void ImageEditor::printCommands() const
{
	std::cout << "Image Editor Commands List" << std::endl;
	std::cout << "load <args_1> <args_2> ... <args_n> - Start a new session" << std::endl;
	std::cout << "add <args_1> <args_2> ... <args_n> - Add new images to the current session" << std::endl;
	std::cout << "grayscale - Apply grayscale effect to images in current session" << std::endl;
	std::cout << "monochrome - Apply grayscale effect to images in current session" << std::endl;
	std::cout << "negative - Apply negative effect to images in current session" << std::endl;
	std::cout << "rotate <left/right> - Rotate images in current session" << std::endl;
	std::cout << "collage <horizontal/vertical> <image_1> <image_2> <output_image> - Create collage of two images" << std::endl;
	std::cout << "undo - Revert the last applied effect on images in current session" << std::endl;
	std::cout << "session info - Print information about the current session" << std::endl;
	std::cout << "switch <num> - Switch to different session" << std::endl;
	std::cout << "help - Print all available commands" << std::endl;
	std::cout << "save - Save all changes and terminate" << std::endl;
	std::cout << "saveAs - Save all changes to the first image and terminate" << std::endl;
	std::cout << "close - Remove last added image from current session" << std::endl;
	std::cout << "exit - Terminate all sessions" << std::endl;
}

// the Singleton deletes itself implicitly, but I added it explicitly, so that the data is deleted before "return 0;" in main.cpp, due to the static Singleton instance
ImageEditor::~ImageEditor() noexcept
{
	this->sessionManager.~SessionManager();
}
#include <iostream>

#include "ImageEditor/ImageEditor.h"

int main()
{
	try
	{
		ImageEditor editor;
		editor.runImageEditor();
	}
	catch (const std::invalid_argument& exc)
	{
		std::cout << "Error: " << exc.what() << std::endl;
	}
	catch (const std::out_of_range& exc)
	{
		std::cout << "Error: " << exc.what() << std::endl;
	}
	catch (const std::logic_error& exc)
	{
		std::cout << "Error: " << exc.what() << std::endl;
	}
	catch (const std::runtime_error& exc)
	{
		std::cout << "Error: " << exc.what() << std::endl;
	}
	catch (const std::exception& exc)
	{
		std::cout << "Error: " << exc.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown error!" << std::endl;
	}

	return 0;
}
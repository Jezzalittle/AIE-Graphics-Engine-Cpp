
#include <memory>
#include "Application3D.h"
#include <iostream>
#include <string>

int main()
{
	std::unique_ptr<Application3D> app = std::make_unique<Application3D>();

	bool fullscreen = false;
	std::string input = "";
	int width = 0;
	int height = 0;

	while (input != "y" || input != "Y" || input != "n" || input != "N")
	{
		std::cout << "Use Fullscreen (Y/N)\n";
		std::cin >> input;
		std::cout << std::endl;

		if (input == "y" || input == "Y")
		{
			fullscreen = true;
			break;
		}
		else if(input == "n" || input == "N")
		{
			fullscreen = false;
			break;
		}

		input = "";

	}


	while (width == 0)
	{
		std::cout << "Width?\n";
		std::cin >> width;
		std::cout << std::endl;
	}
	while (height == 0)
	{
		std::cout << "Height?\n";
		std::cin >> height;
		std::cout << std::endl;
	}


	return app->run("OpenGL Engine", width, height, fullscreen);
}
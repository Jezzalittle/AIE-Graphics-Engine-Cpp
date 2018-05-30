
#include <memory>
#include "Application3D.h"

int main()
{
	std::unique_ptr<Application3D> app = std::make_unique<Application3D>();
	return app->run("Test App", 1280, 720);
}
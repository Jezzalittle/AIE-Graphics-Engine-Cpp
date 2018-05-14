#include "Application.h"


int main()
{

	auto app = new Application("lel",1280,720);
	app->Startup();
	delete app;
	return 0;

}

#include <gl_core_4_4.h>
#include <glfw/glfw3.h>
#include <iostream>

int main()
{
	if (glfwInit() == false)
	{
		return -1;
	}



	GLFWwindow* window = glfwCreateWindow(1290,720, "GraphicsTest", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() != ogl_LOAD_SUCCEEDED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	std::cout << major << "." << minor << std::endl;

	
	glEnable(GL_DEPTH);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 1.0f, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//do our drawing

	glfwDestroyWindow(window);

	glfwTerminate();




	return 0;
}
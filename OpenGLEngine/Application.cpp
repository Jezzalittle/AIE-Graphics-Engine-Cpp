#include "Application.h"
#include <gl_core_4_4.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <Gizmos.h>

Application::Application(const char * a_windowName, int a_width, int a_height)
{
	m_windowName = a_windowName;
	m_width = a_width;
	m_height = a_height;
}

int Application::Startup()
{
	if (glfwInit() == false)
	{
		return -1;
	}



	m_window = glfwCreateWindow(m_width, m_height, m_windowName, nullptr, nullptr);

	if (m_window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(m_window);

	if (ogl_LoadFunctions() != ogl_LOAD_SUCCEEDED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	std::cout << major << "." << minor << std::endl;

	glEnable(GL_DEPTH);

	Run();

	return 0;
}

void Application::Run(const char* a_windowName, int a_width, int a_height)
{
	if (createWindow(a_windowName, a_width, a_height) == 0 && Startup() == 0)
	{
		while (!glfwWindowShouldClose(m_window))
		{
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}

}


Application::~Application()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

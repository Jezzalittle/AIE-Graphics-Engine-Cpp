#include "Application.h"
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Input.h"
#include "imgui_glfw3.h"
#include <Gizmos.h>




using namespace aie;

Application::Application()
{
	m_window = nullptr;
	m_windowName = nullptr;
	m_width = 0;
	m_height = 0;
	m_startTime = ::std::chrono::high_resolution_clock::now();
	m_lastFrameTime = m_startTime;
	m_elapsedTime = 0.0f;
}


void Application::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

int Application::createWindow(const char* a_windowName, int a_width, int a_height)
{
	m_windowName = a_windowName;
	m_width = a_width;
	m_height = a_height;

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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// start input manager
	Input::create();

	// imgui
	ImGui_Init(m_window, true);

	return 0;
}

void Application::shutdown()
{
	ImGui_Shutdown();
	Input::destroy();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}


Application::~Application()
{

}

int Application::run(const char * a_windowName, int a_width, int a_height)
{
	if (createWindow(a_windowName, a_width, a_height) == 0 && onStartup() == 0)
	{
		while (!glfwWindowShouldClose(m_window) || glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			auto now = std::chrono::high_resolution_clock::now();
			auto timeTaken = now - m_lastFrameTime;
			m_dt = std::chrono::duration<float>(timeTaken).count();
			m_lastFrameTime = now;
			m_elapsedTime = (float)(now - m_startTime).count();


			// clear input
			Input::getInstance()->clearStatus();

			glfwPollEvents();


			glClearColor(m_backgroundColour.x, m_backgroundColour.y, m_backgroundColour.z, m_backgroundColour.w);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// clear imgui
			ImGui_NewFrame();

			update();
			draw();

			// draw IMGUI last
			ImGui::Render();

			glfwSwapBuffers(m_window);


		}

		onShutdown();
		shutdown();

	}
	return 0;
}

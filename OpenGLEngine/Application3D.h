#pragma once
#include "Application.h"
class Application3D : public Application
{
public:

	Application3D(const char* a_windowName, int a_width, int a_height) : Application(m_windowName, m_width, m_height) {}

	void Run();

	Application3D() = delete;
	~Application3D();
};


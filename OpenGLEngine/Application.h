#pragma once
#include <chrono>
#include <glm\ext.hpp>
#include <glm\glm.hpp>

class Application {
public:


	Application();

	virtual ~Application();

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual int onStartup() = 0;
	virtual void onShutdown() = 0;
	int run(const char* a_windowName, int a_width, int a_height);

	float getElapsedTime() { return m_elapsedTime; }
	float getDeltaTime() { return m_dt; }
	int getWindowWidth() { return m_width; }
	int getWindowHeight() { return m_height; }
	const char* getWindowName() { return m_windowName; }
	class GLFWwindow* getWindow() { return m_window;  }


protected:

	void setBackgroundColour(float x, float y, float z) { m_backgroundColour = glm::vec4(x, y, z, 1.0f); }
	void clearScreen();

private:

	
	glm::vec4 m_backgroundColour;
	float m_elapsedTime;
	std::chrono::high_resolution_clock::time_point m_startTime;
	std::chrono::high_resolution_clock::time_point m_lastFrameTime;
	float m_dt;
	class GLFWwindow* m_window;
	int m_width;
	int m_height;
	const char* m_windowName;
	int createWindow(const char* a_windowName, int a_width, int a_height);
	void shutdown();

};

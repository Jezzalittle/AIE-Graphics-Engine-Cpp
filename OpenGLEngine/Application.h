#pragma once
class Application {
public:

	Application();

	Application() = delete;
	~Application();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual int Startup() = 0;
	virtual void Shutdown() = 0;
	virtual void Run();

protected:

	
	int createWindow(const char* a_windowName, int a_width, int a_height)

	const char* m_windowName;
	int m_width;
	int m_height;
	class GLFWwindow* m_window;
};

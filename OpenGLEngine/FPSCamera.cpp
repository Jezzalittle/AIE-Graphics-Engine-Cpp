#include "FPSCamera.h"
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>


FPSCamera::FPSCamera(float a_speed, float a_rotspeed)
{
	m_moveSpeed = a_speed;
	m_roatateSpeed = a_rotspeed;
	m_mousePostion = glm::vec2();
}

void FPSCamera::update(struct GLFWwindow* window, float dt)
{
	if (window == nullptr) return;


	auto wUp = glm::vec4{0,1,0,0};

	

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		translate(-m_forward * dt * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		translate(m_forward * dt * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		translate(-m_right * dt * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		translate(m_right * dt * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		translate(wUp * dt * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		translate(-wUp * dt * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		lookAt({ 0,getPosition().y,0 });
	}


	if (glfwGetKey(window, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS)
	{
		//glfwGetCursorPos(window,);
//		translate(-m_forward * dt * m_moveSpeed);
	}



}


FPSCamera::~FPSCamera()
{
}

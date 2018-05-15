#include "FPSCamera.h"
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>


FPSCamera::FPSCamera()
{
}

void FPSCamera::update(struct GLFWwindow* window, float dt)
{
	if (window == nullptr) return;

	auto& forward = getTrasform()[2];
	auto& right = getTrasform()[0];
	auto& up = getTrasform()[1];

	auto wUp = glm::vec4{0,1,0,0};

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		translate(-forward * dt * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		translate(forward * dt * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		translate(-right * dt * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		translate(right * dt * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{

		translate(wUp * dt * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		translate(-wUp * dt * m_moveSpeed);
	}

}


FPSCamera::~FPSCamera()
{
}

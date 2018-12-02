#include "SpinCamera.h"
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <iostream>

SpinCamera::SpinCamera(float a_speed, glm::vec2 a_dir, glm::vec3 a_lookAtPos)
{
	m_moveSpeed = a_speed;
	m_direction = glm::vec4(a_dir.x, a_dir.y, 0, 0);
	m_lookAtPos = a_lookAtPos;

}

void SpinCamera::update(struct GLFWwindow* window, float dt)
{
	if (window == nullptr) return;


	auto wUp3 = glm::vec3{ 0,1,0 };
	auto wUp4 = glm::vec4{ 0,1,0,0 };

	glm::vec4 dir = m_right * m_direction.x + m_up * m_direction.y;
	
	float oldVecBetweenDistance = glm::length(m_lookAtPos - glm::vec3(getPosition().x, getPosition().y, getPosition().z));

	translate(dir * dt * m_moveSpeed);

	lookAt(m_lookAtPos);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		translate(-m_forward * dt * m_moveSpeed);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		translate(m_forward * dt * m_moveSpeed);
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_lookAtPos += wUp3 * dt * m_moveSpeed;
		translate(wUp4 * dt * m_moveSpeed);

	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_lookAtPos += -wUp3 * dt * m_moveSpeed;
		translate(-wUp4 * dt * m_moveSpeed);

	}
	else
	{
		float newVecBetween = glm::length(m_lookAtPos - glm::vec3(getPosition().x, getPosition().y, getPosition().z));

		float foward = oldVecBetweenDistance - newVecBetween;

		translate(m_forward * foward);

	}

}


SpinCamera::~SpinCamera()
{
}

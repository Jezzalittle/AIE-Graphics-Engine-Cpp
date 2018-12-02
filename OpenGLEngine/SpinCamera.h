#pragma once
#include "Camera.h"
class SpinCamera :
	public Camera
{
public:
	
	SpinCamera(float a_speed, glm::vec2 a_dir, glm::vec3 a_lookAt);
	SpinCamera() = delete;



	void update(struct GLFWwindow* window, float dt) override;

	~SpinCamera();

private:

	float m_moveSpeed;
	glm::vec4 m_direction;
	glm::vec3 m_lookAtPos;

};


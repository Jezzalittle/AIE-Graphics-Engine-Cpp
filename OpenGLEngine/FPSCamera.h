#pragma once
#include "Camera.h"
class FPSCamera : public Camera
{
public:

	FPSCamera(float a_speed, float a_rotSpeed);
	FPSCamera() = delete;

	void update(struct GLFWwindow* window, float dt) override;

	float getMoveSpeed() { return m_moveSpeed; }
	void setMoveSpeed(float a_speed) { m_moveSpeed = m_moveSpeed; }



	~FPSCamera();



private:

	glm::vec2 m_mousePostion;
	float m_moveSpeed;
	float m_roatateSpeed;
};


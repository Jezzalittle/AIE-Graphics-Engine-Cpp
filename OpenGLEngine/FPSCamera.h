#pragma once
#include "Camera.h"
class FPSCamera : public Camera
{
public:

	FPSCamera();

	void update(struct GLFWwindow* window, float dt) override;

	float getMoveSpeed() { return m_moveSpeed; }
	void setMoveSpeed(float a_speed) { m_moveSpeed = m_moveSpeed; }



	~FPSCamera();



private:
	float m_moveSpeed;
	float m_roatateSpeed;
};


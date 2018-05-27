#include "Camera.h"



Camera::Camera()
{
	m_worldTransform = glm::mat4(1);
	m_projectionMatrix = glm::mat4(1);
	m_hasSetProjectionMatrix = false;
	m_hasSetViewMatrix = false;
}


Camera::~Camera()
{
}

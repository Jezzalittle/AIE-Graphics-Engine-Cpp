#include "Camera.h"



Camera::Camera()
{
	m_worldTrasform = glm::mat4(1);
	m_projection = glm::mat4(1);
	m_hasSetProjectionMatrix = false;

}


Camera::~Camera()
{
}

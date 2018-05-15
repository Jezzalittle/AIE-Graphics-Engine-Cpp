#pragma once

#include <glm/ext.hpp>
#include <glm/glm.hpp>

class Camera
{
public:
	
	Camera();
	
	
	void translate(glm::vec4 amount) { m_worldTrasform[3] += amount; }
	

	const glm::mat4& getTrasform() const { return m_worldTrasform; }
	glm::mat4& getTrasform() { return m_worldTrasform; }

	glm::vec4 getPosition() const { return m_worldTrasform[3]; };
	void setPosition(glm::vec4 position) { m_worldTrasform[3] = position; }

	void setViewMat(glm::mat4 mat) { m_worldTrasform = glm::inverse(mat); }
	glm::mat4 getViewMat() const { return glm::inverse(m_worldTrasform); }


	const glm::mat4& getProjection() const { assert(m_hasSetProjectionMatrix); return m_projection;  }
	void setProjectionMat(glm::mat4 mat) { m_projection * mat; m_hasSetProjectionMatrix = true; }

	virtual void update(struct GLFWwindow* window, float dt) {};


	virtual ~Camera();


private:

	bool m_hasSetProjectionMatrix;
	glm::mat4 m_projection;
	glm::mat4 m_worldTrasform;
};


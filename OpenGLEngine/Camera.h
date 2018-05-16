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

	void setView(glm::mat4 mat) { m_view = mat; }
	glm::mat4 getView() const { return m_view; }

	const glm::mat4& getProjection() const { assert(m_hasSetProjectionMatrix); return m_projection; }
	void setProjection(glm::mat4 mat)
	{
		m_projection = mat;
		if (m_view == glm::mat4(1))
		{
			m_view = glm::inverse(m_projection);
		}

		m_hasSetProjectionMatrix = true;
	}

	glm::mat4 getClipSpace() { return m_projection * m_view;  }


	virtual void update(struct GLFWwindow* window, float dt) {};



	virtual ~Camera();


private:

	bool m_hasSetProjectionMatrix;
	glm::mat4 m_projection;
	glm::mat4 m_worldTrasform;
	glm::mat4 m_view;

};


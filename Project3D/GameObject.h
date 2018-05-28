#pragma once

#include <OBJMesh.h>
#include <glm\ext.hpp>
#include <glm\glm.hpp>

class GameObject
{
public:

	GameObject();

	void setTrasform(glm::mat4 a_trasform) { m_transform = a_trasform; }
	glm::mat4 getTrasform() { return m_transform; }

	void loadMesh(const char* a_path);
	aie::OBJMesh& getMesh() { return *m_mesh; }



	~GameObject();



private:

	const char* m_path;
	glm::mat4 m_transform;
	aie::OBJMesh* m_mesh;

};


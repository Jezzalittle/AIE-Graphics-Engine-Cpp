#include "GameObject.h"


GameObject::GameObject()
{
	m_transform = glm::mat4(1);
	m_mesh = new aie::OBJMesh();
}



void GameObject::loadMesh(const char * a_path)
{
	if (m_mesh->load(a_path) == false)
	{
		printf(a_path);
	}
}

GameObject::~GameObject()
{
}

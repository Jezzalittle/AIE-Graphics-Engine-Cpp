#include "GameObject.h"

#include "Camera.h"

GameObject::GameObject()
{
	m_transform = glm::mat4(1);
	m_texture = nullptr;
	m_mesh = nullptr;
	m_texturePath = "";
	m_meshPath = "";
}

GameObject::GameObject(const char * a_meshPath, glm::mat4 a_trasform) : GameObject(a_trasform)
{
	m_meshPath = a_meshPath;
	m_mesh = new aie::OBJMesh();
	if (m_meshPath != "")
	{
		loadMesh(m_meshPath);
	}
}

GameObject::GameObject(const char * a_meshPath, glm::mat4 a_trasform, const char* a_texturePath) : GameObject(a_meshPath, a_trasform)
{
	m_texturePath = a_texturePath;
	m_texture = new aie::Texture();
	if (m_texturePath != "")
	{
		loadTexture(m_texturePath);
	}
}





void GameObject::bindTransform(aie::ShaderProgram * a_shader, Camera* a_cam)
{
	assert(a_shader != nullptr);
	assert(a_cam != nullptr);
	glm::mat4 pvm = a_cam->getProjectionView() * m_transform;
	a_shader->bindUniform("ProjectionViewModel", pvm);

}

void GameObject::loadMesh(const char * a_path)
{

	if (m_mesh->load(a_path, true, true) == false)
	{
		printf(a_path);
	}
}

void GameObject::loadTexture(const char * a_path)
{
	if (m_texture->load(a_path) == false) 
	{
		printf(a_path);
	}
}

void GameObject::draw()
{
	m_mesh->draw();
}

GameObject::~GameObject()
{
	if (m_mesh != nullptr)
	{
		delete(m_mesh);
	}
}

#include "GameObject.h"
#include "Application3D.h"
#include "Camera.h"



GameObject::GameObject()
{
}

GameObject::GameObject(const char * a_meshPath, glm::mat4 a_trasform, const char * a_texturePath, const char* a_vertPath, const char* a_fragPath, Camera* a_cam)
{

	m_transform = a_trasform;

	m_cam = a_cam;

	m_shader = aie::ShaderProgram();

	m_texturePath = a_texturePath;
	m_textureDiff = new aie::Texture();
	if (m_texturePath != "")
	{
		loadTexture(m_texturePath);
	}

	m_meshPath = a_meshPath;

	m_mesh = new aie::OBJMesh();
	

	m_shader.loadShader(aie::eShaderStage::VERTEX, a_vertPath);
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, a_fragPath);

	

	if (m_meshPath != "")
	{
		loadMesh(m_meshPath);
	}

	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
	}

}


void GameObject::bindShader()
{
	// bind shader
	m_shader.bind();

	assert(m_cam != nullptr);

	glm::mat4 pvm = m_cam->getProjectionView() * m_transform;
	m_shader.bindUniform("ProjectionViewModel", pvm);

	m_shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_transform)));

	m_shader.bindUniform("ModelMatrix", m_transform);


	if (m_light != nullptr)
	{

		m_shader.bindUniform("Ia", { 0.25f, 0.25f, 0.25f });
		m_shader.bindUniform("Id", m_light->diffuse);
		m_shader.bindUniform("Is", m_light->specular);
		m_shader.bindUniform("LightDirection", m_light->direction);

		m_shader.bindUniform("cameraPosition", m_cam->getPosition());
	}



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
	if (m_textureDiff->load(a_path) == false)
	{
		printf(a_path);
	}
}

void GameObject::draw()
{
	//binding shader values
	bindShader();

	if (m_mesh != nullptr)
	{
		m_mesh->draw();
	}
}

GameObject::~GameObject()
{
	if (m_mesh != nullptr)
	{
		delete(m_mesh);
	}
}

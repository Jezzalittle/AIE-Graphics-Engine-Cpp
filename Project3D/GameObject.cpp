#include "GameObject.h"
#include "Application3D.h"
#include "Camera.h"

GameObject::GameObject()
{
}

GameObject::GameObject(const char * a_meshPath, glm::mat4 a_trasform, const char* a_vertPath, const char* a_fragPath, Camera* a_cam)
{

	m_transform = a_trasform;

	m_cam = a_cam;

	m_shader = aie::ShaderProgram();


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


	for (size_t i = 0; i < m_lights.size(); i++)
	{
		m_shader.bindUniform(("lights[" + std::to_string(i) + "].m_direction").c_str(), m_lights[i]->direction);
		m_shader.bindUniform(("lights[" + std::to_string(i) + "].m_ambient").c_str(), m_lights[i]->ambientLight);
		m_shader.bindUniform(("lights[" + std::to_string(i) + "].m_diffuse").c_str(), m_lights[i]->diffuse);
		m_shader.bindUniform(("lights[" + std::to_string(i) + "].m_specular").c_str(), m_lights[i]->specular);
	}

	m_shader.bindUniform("HasTextures", 1);



	m_shader.bindUniform("cameraPosition", m_cam->getPosition());




}


void GameObject::loadMesh(const char * a_path)
{
	if (m_mesh->load(a_path,true,true) == false)
	{ 
		printf("Dragon Mesh Error!\n");   
	}
}



void GameObject::Update()
{

	//ImGui::Text("Hello, world %d", 123);


	//for (size_t i = 0; i < m_lights.size(); i++)
	//{
	//	ImGui::InputFloat3("light " + i, glm::value_ptr(m_lights[i]->ambientLight));
	//}
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

#pragma once

#include <OBJMesh.h>
#include <glm\ext.hpp>
#include <glm\glm.hpp>
#include <Shader.h>
#include <assert.h>


class ShaderProgram;
class Camera;

class GameObject
{
public:

	GameObject();
	GameObject(glm::mat4 a_trasform) { m_transform = a_trasform; };
	GameObject(const char* a_meshPath, glm::mat4 a_trasform);
	GameObject(const char* a_meshPath, glm::mat4 a_trasform, const char* a_texturepath);
	GameObject(GameObject&& other)
	{
		m_texture = std::move(other.m_texture);
		other.m_texture = nullptr;


		m_mesh = std::move(other.m_mesh);
		other.m_mesh = nullptr;

		m_texturePath = other.m_texturePath;
		m_meshPath = other.m_meshPath;
		m_transform = other.m_transform;
	}
	
	// Move Constructor
	GameObject& operator= (GameObject&& other)
	{
		m_texture = std::move(other.m_texture);
		other.m_texture = nullptr;


		m_mesh = std::move(other.m_mesh);
		other.m_mesh = nullptr;

		m_texturePath = other.m_texturePath;
		m_meshPath = other.m_meshPath;
		m_transform = other.m_transform;

		return *this;

	}


	void setTrasform(glm::mat4 a_trasform) { m_transform = a_trasform; }
	glm::mat4 getTrasform() { return m_transform; }


	void bindTransform(aie::ShaderProgram* a_shader, Camera* a_cam);

	void loadMesh(const char* a_path);
	void loadTexture(const char* a_path);

	aie::OBJMesh& getMesh() { assert(m_mesh == nullptr); return *m_mesh; }

	void draw();


	~GameObject();



private:

	aie::Texture* m_texture;
	const char* m_texturePath;
	const char* m_meshPath;
	glm::mat4 m_transform;
	aie::OBJMesh* m_mesh;

};


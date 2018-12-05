#pragma once

#include <glm\ext.hpp>
#include <glm\glm.hpp>
#include <Shader.h>
#include <assert.h>
#include <Mesh.h>
#include <vector>
#include <RenderTarget.h>
#include <OBJMesh.h>


class ShaderProgram;
class Camera;
struct Light;

class GameObject
{
public:
	GameObject(); 
	GameObject(glm::mat4 a_trasform) { m_transform = a_trasform; };
	GameObject(const char* a_meshPath, glm::mat4 a_trasform, const char* a_vertPath, const char* a_fragPath, Camera* a_cam);
	GameObject(GameObject&& other)
	{

		m_mesh = std::move(other.m_mesh);
		other.m_mesh = nullptr;

		m_meshPath = other.m_meshPath;
		m_transform = other.m_transform;
	}

	// Move Constructor
	GameObject& operator= (GameObject&& other)
	{

		m_cam = std::move(other.m_cam);
		other.m_cam = nullptr;

		m_mesh = std::move(other.m_mesh);
		other.m_mesh = nullptr;

		m_shader = other.m_shader;
		m_meshPath = other.m_meshPath;
		m_transform = other.m_transform;

		return *this;

	}


	void setTrasform(glm::mat4 a_trasform) { m_transform = a_trasform; }
	glm::mat4 getTrasform() { return m_transform; }

	void setLight(Light* a_light) { m_lights.push_back(a_light); }

	void loadMesh(const char* a_path);
	void loadTexture(const char* a_path);

	aie::OBJMesh& getMesh() { assert(m_mesh != nullptr); return *m_mesh; }
	
	void setShader(aie::ShaderProgram* a_shader) { m_shader = a_shader;  }
	aie::ShaderProgram* getShader() { return m_shader; }

	void Update();
	void draw();


	~GameObject();



private:
	
	void bindShader();

	std::vector<Light*> m_lights;

	Camera* m_cam;
	aie::ShaderProgram* m_shader;


	const char* m_meshPath;
	glm::mat4 m_transform;
	aie::OBJMesh* m_mesh;

};


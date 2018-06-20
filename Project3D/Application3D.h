#pragma once
#include <Application.h>
#include <Mesh.h>
#include <glm\ext.hpp>
#include <glm\glm.hpp>
#include <Shader.h>
#include <FPSCamera.h>

#include "GameObject.h"

class Application3D : public Application
{
public:

	Application3D() : Application() {};
	virtual int onStartup();
	virtual void onShutdown();
	virtual void update();
	virtual void draw();

	virtual ~Application3D();




protected:


	glm::vec3 m_ambientLight;
	Light* m_light;
	Light* m_light2;


	FPSCamera* m_cam;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;



	GameObject* m_soulSpear;


	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;
	
private:

	float m_lightRotTimer;


};

	struct Light
	{
		Light() { direction = glm::vec3(); diffuse = glm::vec3(); specular = glm::vec3(); ambientLight = glm::vec3(); }
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 ambientLight;
	};

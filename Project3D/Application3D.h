#pragma once
#include <Application.h>
#include <Mesh.h>
#include <glm\ext.hpp>
#include <glm\glm.hpp>
#include <Shader.h>
#include <SpinCamera.h>
#include <RenderTarget.h>
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


	SpinCamera* m_cam;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	GameObject* m_soulSpear;

	Mesh m_fullscreenQuad;
	aie::ShaderProgram m_postShader;



	aie::RenderTarget m_renderTarget;

	
private:

	float m_lightRotTimer;
	float m_lightRotTimer2;


};

	struct Light
	{
		Light() { direction = glm::vec3(); diffuse = glm::vec3(); specular = glm::vec3(); ambientLight = glm::vec3(); }
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 ambientLight;
	};

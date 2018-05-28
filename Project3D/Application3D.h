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

	Application3D() : Application() {}
	virtual int onStartup();
	virtual void onShutdown();
	virtual void update();
	virtual void draw();

	virtual ~Application3D();

protected:

	FPSCamera* m_cam;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	aie::ShaderProgram m_shader;


	GameObject m_bunny;
	aie::OBJMesh  m_bunnyMesh;
	glm::mat4 m_bunnyTransform;

	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;
};


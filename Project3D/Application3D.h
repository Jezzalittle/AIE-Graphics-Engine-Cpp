#pragma once
#include <Application.h>
#include <Mesh.h>
#include <glm\ext.hpp>
#include <glm\glm.hpp>
#include <Shader.h>
#include <Camera.h>

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

	Camera* cam;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	aie::ShaderProgram m_shader;
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;
};


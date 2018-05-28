#include "Application3D.h"
#include <Gizmos.h>



int Application3D::onStartup()
{
	m_cam = new FPSCamera(5,5);

	m_bunny = GameObject();
	setBackgroundColour(0, 0, 0);
	// initialise gizmo primitive counts
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_cam->setViewMatrix(glm::lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0, 1, 0)));
	m_cam->setProjectionMatrix(glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f));

	
	m_shader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/simple.frag");

	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	//adding bunny mesh

	m_bunny.loadMesh("./stanford/bunny.obj");
	m_bunny.setTrasform({
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		0,0,0,1
	});

	m_quadMesh.initialiseQuad();

	//make the quad 10 units wide
	m_quadTransform = {
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1 };





	return 0;
}

void Application3D::onShutdown()
{
}

void Application3D::update()
{
	m_cam->update(getWindow(), getDeltaTime());
}

void Application3D::draw()
{
	// wipe the screen to the background colour
	clearScreen();


	// update perspective in case window resized


	// bind shader
	m_shader.bind();

	// bind transform
	auto pvm = m_cam->getProjectionView() * m_bunnyTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);


	//draw bunny
	m_bunny.getMesh().draw();

	// bind transform
	pvm = m_cam->getProjectionView() * m_quadTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);

	// draw quad
	m_quadMesh.draw();




	aie::Gizmos::addTransform(glm::mat4(1));

	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i)
	{
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
		
		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i),i == 10 ? white : black);
	}


	// draw 3D gizmos
	aie::Gizmos::draw(m_cam->getProjectionView());

	// draw 2D gizmos using an orthogonal projection matrix
	aie::Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());

}


Application3D::~Application3D()
{
}

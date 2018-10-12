#include "Application3D.h"
#include <Gizmos.h>



int Application3D::onStartup()
{
	m_cam = new FPSCamera(10, 5);

	m_soulSpear = new GameObject("./soulspear/soulspear.obj", 
								{ 1, 0, 0, 0,
								  0, 1, 0, 0,
								  0, 0, 1, 0,
								  0, 0, 0, 1 },
								"./shaders/PBR.vert",
								"./shaders/PBR.frag",
								m_cam);


	m_light = new Light();
	m_light->direction = { 0, 0, -1};
	m_light->diffuse = { 0.5f, 0.5f, 0.5f };
	m_light->specular = { 0.5f, 0.5f, 0.5f };
	m_light->ambientLight = { 0, 0, 0 };



	m_soulSpear->setLight(m_light);
	//m_soulSpear->setLight(m_light2);


	setBackgroundColour(0.5f, 0.5, 0.5f);
	// initialise gizmo primitive counts
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_cam->setViewMatrix(glm::lookAt(glm::vec3(10,0,10), glm::vec3(0,0,1), glm::vec3(0, 1, 0)));
	m_cam->setProjectionMatrix(glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f));

	m_lightRotTimer = 0.0f;
	m_lightRotTimer2 = 0.0f;



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
	m_lightRotTimer2 += getDeltaTime() * 0.5;
	m_lightRotTimer += getDeltaTime();
	// rotate light
	//m_light->direction = glm::normalize(glm::vec3(glm::cos(m_lightRotTimer), glm::sin(m_lightRotTimer), 0));

//	m_light2->direction = glm::normalize(glm::vec3(-glm::cos(m_lightRotTimer2), -glm::sin(m_lightRotTimer2), 0));
	m_cam->update(getWindow(), getDeltaTime());
}

void Application3D::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	//draw bunny

	// bind transform
	//auto pvm = m_cam->getProjectionView() * m_quadTransform;
	//m_shader.bindUniform("ProjectionViewModel", pvm);
	

	m_soulSpear->draw();
	
	// draw quad
	//m_quadMesh.draw();


	//aie::Gizmos::addTransform(glm::mat4(1));

	//glm::vec4 white(1);
	//glm::vec4 black(0, 0, 0, 1);
	//for (int i = 0; i < 21; ++i)
	//{
	//	aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);

	//	aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
	//}


	// draw 3D gizmos
	aie::Gizmos::draw(m_cam->getProjectionView());

	// draw 2D gizmos using an orthogonal projection matrix
	aie::Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());

}


Application3D::~Application3D()
{
	delete(m_light);
	delete(m_light2);
	delete(m_soulSpear);
}

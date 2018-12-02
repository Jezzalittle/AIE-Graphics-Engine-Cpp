#include "Application3D.h"
#include <Gizmos.h>
#include "imgui.h"
#include <iostream>


int Application3D::onStartup()
{
	m_cam = new SpinCamera(10.0f, glm::vec2(1, 0), glm::vec3(0, 0, 0));

	m_soulSpear = new GameObject("./soulspear/soulspear.obj",
		{ 1, 0, 0, 0,
		  0, 1, 0, 0,
		  0, 0, 1, 0,
		  0, 0, 0, 1 },
		"./shaders/PBRTest1.vert",
		"./shaders/PBRTest1.frag",
		m_cam);

	m_light = new Light();
	m_light->direction = { -1, -1, -1 };
	m_light->diffuse = { 1, 0, 0 };
	m_light->specular = { 1, 0, 0 };
	m_light->ambientLight = { 0, 0, 0 };



	m_soulSpear->setLight(m_light);
	//m_soulSpear->setLight(m_light2);


	setBackgroundColour(0.5f, 0.5, 0.5f);
	// initialise gizmo primitive counts
	aie::Gizmos::create(10000, 10000, 10000, 10000);



	// create simple camera transforms
	m_cam->setViewMatrix(glm::lookAt(glm::vec3(10, 0, 10), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0)));
	m_cam->setProjectionMatrix(glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f));

	m_lightRotTimer = 0.0f;
	m_lightRotTimer2 = 0.0f;


	if (m_renderTarget.initialise(1, getWindowWidth(), getWindowHeight()) == false)
	{
		printf("Render Target Error!\n");
		return 0;
	}



	// create a fullscreen quad
	m_fullscreenQuad.initialiseFullscreenQuad();




	// load a post-processing shader
	m_postShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/post.vert");
	m_postShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/post.frag");
	if (m_postShader.link() == false)
	{
		printf("Post Shader Error: %s\n",
			m_postShader.getLastError());
		return 0;
	}



	return 0;
}

void Application3D::onShutdown()
{
}

void Application3D::update()
{
	m_lightRotTimer2 += getDeltaTime() * 0.5f;
	m_lightRotTimer += getDeltaTime();

	// rotate light
	//m_light->direction = glm::normalize(glm::vec3(glm::cos(m_lightRotTimer), glm::sin(m_lightRotTimer), 0));

	m_soulSpear->Update();

	m_cam->update(getWindow(), getDeltaTime());


}

void Application3D::draw()
{


	// bind our render target
	m_renderTarget.bind();

	// wipe the screen to the background colour
	clearScreen();

	m_soulSpear->draw();


	aie::Gizmos::addTransform(glm::mat4(1));


	//// draw 3D gizmos
	aie::Gizmos::draw(m_cam->getProjectionView());

	//// draw 2D gizmos using an orthogonal projection matrix
	aie::Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());

	// unbind target to return to backbuffer
	m_renderTarget.unbind();

	clearScreen();





	m_postShader.bind();
	m_postShader.bindUniform("colourTexture", 0);
	m_renderTarget.getTarget(0).bind(0);


	m_fullscreenQuad.draw();





	//ImGui::Begin("test");
	//ImGui::Text("hello World");
	//ImGui::End();

}


Application3D::~Application3D()
{
	delete(m_light);
	delete(m_light2);
	delete(m_soulSpear);
}

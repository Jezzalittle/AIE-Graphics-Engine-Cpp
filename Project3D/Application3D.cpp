#include "Application3D.h"
#include <Gizmos.h>
#include "imgui.h"
#include <iostream>
#include "gl_core_4_4.h"


int Application3D::onStartup()
{
	m_cam = new SpinCamera(10.0f, glm::vec2(1, 0), glm::vec3(0, 0, 0));

	m_soulSpear = new GameObject("./soulspear/soulspear.obj",
		{ 1, 0, 0, 0,
		  0, 1, 0, 0,
		  0, 0, 1, 0,
		  0, 0, 0, 1 },
		"./shaders/PBRTest.vert",
		"./shaders/PBRTest.frag",
		m_cam);

	m_light = new Light();
	m_light->direction = { 0.3f, -0.6f, -1.0f };
	m_light->diffuse = { 9, 6, 0 };
	m_light->specular = { 6, 1, 0 };
	m_light->ambientLight = { 0, 0, 0 };

	m_PBRShader = m_soulSpear->getShader();

	m_soulSpear->setLight(m_light);
	//m_soulSpear->setLight(m_light2);


	setBackgroundColour(255, 255, 255);
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

	// load a phong shader
	m_phongShader = new aie::ShaderProgram();

	m_phongShader->loadShader(aie::eShaderStage::VERTEX,
		"./shaders/phong.vert");
	m_phongShader->loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/phong.frag");
	if (m_phongShader->link() == false)
	{
		printf("phong Shader Error: %s\n",
			m_postShader.getLastError());
		return 0;
	}

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

	m_backgroundColourGUI = getBackgroundColour();
	useBlurGUI = false;
	blurAmountGUI = 2.0f;
	useDistortGUI = false;
	distortAmountGUI = 15.0f;
	PBRShaderGUI = true;


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
	m_postShader.bindUniform("hasBlur", ((useBlurGUI == true) ? 1 : 0));
	m_postShader.bindUniform("blurAmount", blurAmountGUI);
	m_postShader.bindUniform("hasDistort", useDistortGUI);
	m_postShader.bindUniform("distortAmount", distortAmountGUI);
	m_postShader.bindUniform("colourTexture", 0);
	m_renderTarget.getTarget(0).bind(0);

	
	//m_quad.draw();
	m_fullscreenQuad.draw();

	DrawImgui();

}

void Application3D::DrawImgui()
{
	ImGui::Begin("Controls");
	ImGui::Text("'W' = Move Forward");
	ImGui::Text("'S' = Move Back");
	ImGui::Text("'Space' = Move Up");
	ImGui::Text("'Left-Shift' = Move Down");

	ImGui::End();

	ImGui::Begin("Settings");

	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::Text("Application Settings");

	ImGui::Spacing();

	ImGui::ColorEdit3("Background Colour", glm::value_ptr(m_backgroundColourGUI));
	setBackgroundColour(m_backgroundColourGUI.x, m_backgroundColourGUI.y, m_backgroundColourGUI.z);

	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::Text("Post Settings");

	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::Checkbox("Blur Effect", &useBlurGUI);
	ImGui::DragFloat("Blur Amount", &blurAmountGUI, 1.0f, -50.0f, 50.0f);

	ImGui::Spacing();

	ImGui::Checkbox("Distort Effect", &useDistortGUI);
	ImGui::DragFloat("Distort Amount", &distortAmountGUI, 1.0f, -50.0f, 50.0f);

	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::Text("Scene Settings");

	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::Checkbox("PBR or Phong", &PBRShaderGUI);
	m_soulSpear->setShader(((PBRShaderGUI == true) ? m_PBRShader : m_phongShader));
	ImGui::TextWrapped("The PBR Shader is using Cook-Torrance for the Specular Term and Oren-Nayar for the Diffuse Term");



	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::Text("Light Settings");
	ImGui::DragFloat3("Direction", glm::value_ptr(m_light->direction), 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("Diffuse Colour", glm::value_ptr(m_light->diffuse), 1.0f, 0, 255.0f);
	ImGui::DragFloat3("specular Colour", glm::value_ptr(m_light->specular), 1.0f, 0, 255.0f);


	ImGui::End();
}

Application3D::~Application3D()
{
	delete(m_light);
	delete(m_light2);
	delete(m_soulSpear);
	delete(m_phongShader);
}


#include "Graphics_Simulator.h"
#include <algorithm>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Controls.h"
#include "DrawMap.h"



QuadCore::Graphics_Simulator::Graphics_Simulator()
	: display(width_window, height_window, "Graphics Simulator - QuadCore")
{
}


QuadCore::Graphics_Simulator::~Graphics_Simulator()
{
}


void QuadCore::Graphics_Simulator::Run()
{	
	// 1. Object
	Mesh mesh1("../media/shape/Cube.obj");
	//Mesh mesh1("../media/shape/Wedge.obj");
	//Mesh mesh1("../media/shape/CubeHollow.obj");
	Mesh mesh2("../media/shape/CubeHollow.obj");
	Mesh mesh3("../media/shape/Icosphere.obj");
	Mesh SphereMesh("../media/shape/Sphere.obj");
	
	//Mesh nanosuitMesh("../media/objects/nanosuit_reflection/nanosuit.obj");

	

	// 2. Shader
	Shader shader1("../media/new_shader/basicShader_light");
	Shader shader2("../media/new_shader/basicShader_tex");
	//Shader shader1("../media/shaders/cubemaps/cubemaps");
	Shader skyboxShader("../media/shaders/cubemaps/skybox");
	Shader glassShader("../media/shaders/cubemaps/glass");
	Shader mirrorShader("../media/shaders/cubemaps/mirror");

	Shader shader_UI = ("../media/new_shader/basicShader_2D_HUD");

	//3. Texture
	Texture texture1("../media/res/bricks.jpg");
	Texture texture2("../media/skyblue.jpg");
	Texture SlimeTexture("../media/res/slime.jpg");
	Texture JupiterTexture("../media/res/Jupiter.jpg");
	Texture EarthTexture("../media/res/earth.jpg");
	Texture MoonTexture("../media/res/moon.jpg");
	//texture2.Reset();

	

	//4. Transform
	Transform world_transform;
	Transform UI_transform;

	Transform Bullet;
	Transform glassTrans(glm::vec3(10.0, 0, 0));
	Transform mirrorTrans(glm::vec3(-10.0, 0, 0));
	
	
	//5. Camera
	float aspec = (float)width_window / (float)height_window;
	Camera camera(glm::vec3(0, 0, 10), 70.0f, aspec, 0.01F, 1000.0f);

	// Controls (Mouse / Keyboard)
	Controls controls(display.GetWindow());
	Controls controller(controls, camera, world_transform);

	m_world_coordinates.Init(&world_transform, &camera, 50.0f);
	m_UI_coordinates.Init_UI(&UI_transform, &camera, 0.1f);


	m_scene_manager.Init(&camera);

	float counter = 0.0f;

	while (!display.IsClosed())
	{	
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

		display.UpdateWindowSize();	// ȭ�� ����
		camera.Update(camera.GetPos(), 70.0f, display.GetWindowAspec(), 0.01F, 1000.0f);		
				
		display.Clear(0.1f, 0.1f, 0.1f, 1.0f);	// ��� �ʱ�ȭ
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);	// ��� �ʱ�ȭ
		//display.Clear(0.3f, 0.3f, 0.3f, 1.0f);	// ��� �ʱ�ȭ
		
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		// Draw here
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

		//### ����, �ݼ�
		/*
		glassShader.Bind();
		skyboxTexture.Bind(0);
		glassShader.Update(glassTrans, camera);
		nanosuitMesh.Draw();

		mirrorShader.Bind();
		skyboxTexture.Bind(0);
		mirrorShader.Update(mirrorTrans, camera);
		nanosuitMesh.Draw();*/


		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		
		//### �ó������� ��� ���
		m_scene_manager.Play();

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
				

		// ���� ��ǥ�� �׸���
		m_world_coordinates.Draw();
		

		////////////////////////////////////////////////////////////////////
		// UI ��ǥ�� �׸���

		shader_UI.Bind();
		texture1.Bind(0);

		UI_transform.GetPos().x = +0.7f;
		UI_transform.GetPos().y = -0.7f;

		UI_transform.SetRot(camera.GetRot());

		shader_UI.Update(UI_transform, camera);
		m_UI_coordinates.Draw(5.0f);

		////////////////////////////////////////////////////////////////////

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		
		display.Update();	// ȭ�鰻��
		counter += 0.05f;
	}
}

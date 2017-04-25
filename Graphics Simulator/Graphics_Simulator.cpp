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
	float skybox_size = 300.0f;
	Vertex SkyBoxVerties[] = // 스카이박스 vertices
	{
		// back
		Vertex(glm::vec3(-skybox_size, -skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),	// 0
		Vertex(glm::vec3(+skybox_size, -skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),	// 1
		Vertex(glm::vec3(+skybox_size, +skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),	// 2
		Vertex(glm::vec3(-skybox_size, +skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),	// 3

		// front
		Vertex(glm::vec3(-skybox_size, -skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, +1.0f)),	// 4
		Vertex(glm::vec3(+skybox_size, -skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, +1.0f)),	// 5
		Vertex(glm::vec3(+skybox_size, +skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, +1.0f)),	// 6
		Vertex(glm::vec3(-skybox_size, +skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, +1.0f)),	// 7

		// left
		Vertex(glm::vec3(-skybox_size, -skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f, 0.0f)),	// 4 - 8
		Vertex(glm::vec3(-skybox_size, -skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f, 0.0f)),	// 0 - 9
		Vertex(glm::vec3(-skybox_size, +skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f, 0.0f)),	// 3 - 10
		Vertex(glm::vec3(-skybox_size, +skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f, 0.0f)),	// 7 - 11

		// right
		Vertex(glm::vec3(+skybox_size, -skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(+1.0f,  0.0f, 0.0f)),	// 5 - 12
		Vertex(glm::vec3(+skybox_size, -skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(+1.0f,  0.0f, 0.0f)),	// 1 - 13
		Vertex(glm::vec3(+skybox_size, +skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(+1.0f,  0.0f, 0.0f)),	// 2 - 14
		Vertex(glm::vec3(+skybox_size, +skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(+1.0f,  0.0f, 0.0f)),	// 6 - 15

		// top
		Vertex(glm::vec3(-skybox_size, +skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  +1.0f, 0.0f)),	// 3 - 16
		Vertex(glm::vec3(+skybox_size, +skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  +1.0f, 0.0f)),	// 2 - 17
		Vertex(glm::vec3(+skybox_size, +skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  +1.0f, 0.0f)),	// 6 - 18
		Vertex(glm::vec3(-skybox_size, +skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  +1.0f, 0.0f)),	// 7 - 19

		// bottom
		Vertex(glm::vec3(-skybox_size, -skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f, 0.0f)),	// 0 - 20
		Vertex(glm::vec3(+skybox_size, -skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f, 0.0f)),	// 1 - 21
		Vertex(glm::vec3(+skybox_size, -skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f, 0.0f)),	// 5 - 22
		Vertex(glm::vec3(-skybox_size, -skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f, 0.0f)),	// 4 - 23
	};
	unsigned int indices[] = {
		 0, 1, 2,    2, 3, 0,		// back
		 5, 4, 7,    7, 6, 5,		// front
		 8, 9,10,   10,11, 8,		// left
		13,12,15,   15,14,13,		// right
		16,17,18,   18,19,16,		// top
		21,20,23,   23,22,21,		// bottom
	};
	
	//// mesh 삼각형 도형그려주기
	Vertex mesh_vertices[] = {
		//Vertex(glm::vec3(-1.0, -1.0, 0.0),	glm::vec2(0.0, 0.0), glm::vec3(0, 0, 1)),
		//Vertex(glm::vec3(+1.0, -1.0, 0.0),	glm::vec2(1.0, 0.0), glm::vec3(0, 0, 1)),
		//Vertex(glm::vec3(+1.0, +1.0, 0.0),	glm::vec2(1.0, 1.0), glm::vec3(0, 0, 1)),
		//Vertex(glm::vec3(-1.0, +1.0, 0.0),	glm::vec2(0.0, 1.0), glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-0.5, -0.5, 0.0),	glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(+0.5, -0.5, 0.0),	glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(+0.5, +0.5, 0.0),	glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(-0.5, +0.5, 0.0),	glm::vec2(0.0, 1.0)),
	};
	unsigned int mesh_indices[] = {
		0,1,2,
		2,3,0,
	};
	Mesh mesh(mesh_vertices, sizeof(mesh_vertices) / sizeof(mesh_vertices[0]), mesh_indices, sizeof(mesh_indices) / sizeof(mesh_indices[0]));


	
	// 1. Object
	Mesh mesh1("../media/shape/Cube.obj");
	//Mesh mesh1("../media/shape/Wedge.obj");
	//Mesh mesh1("../media/shape/CubeHollow.obj");
	Mesh mesh2("../media/shape/CubeHollow.obj");
	Mesh mesh3("../media/shape/Icosphere.obj");
	Mesh skyboxMesh(SkyBoxVerties, sizeof(SkyBoxVerties) / sizeof(SkyBoxVerties[0]), indices, sizeof(indices) / sizeof(indices[0]));
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
	//texture2.Reset();
	//스카이박스 텍스쳐 들어가는 부분
	std::vector<std::string> faces;
	faces.push_back("../media/textures/skybox/right.jpg");
	faces.push_back("../media/textures/skybox/left.jpg");
	faces.push_back("../media/textures/skybox/top.jpg");
	faces.push_back("../media/textures/skybox/bottom.jpg");
	faces.push_back("../media/textures/skybox/back.jpg");
	faces.push_back("../media/textures/skybox/front.jpg");

	Texture skyboxTexture(faces);
	

	//4. Transform
	Transform world_transform;
	Transform UI_transform;
	Transform transform1;
	Transform transform2;
	Transform transform3;

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


	
	

	while (!display.IsClosed())
	{	
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		display.UpdateWindowSize();	// 화면 갱신
		camera.Update(camera.GetPos(), 70.0f, display.GetWindowAspec(), 0.01F, 1000.0f);		
				
		display.Clear(0.1f, 0.1f, 0.1f, 1.0f);	// 배경 초기화
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);	// 배경 초기화
		//display.Clear(0.3f, 0.3f, 0.3f, 1.0f);	// 배경 초기화
		
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		// Draw here
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		//### 유리, 금속
		/*
		glassShader.Bind();
		skyboxTexture.Bind(0);
		glassShader.Update(glassTrans, camera);
		nanosuitMesh.Draw();

		mirrorShader.Bind();
		skyboxTexture.Bind(0);
		mirrorShader.Update(mirrorTrans, camera);
		nanosuitMesh.Draw();*/

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		
		

		//### 시나리오별 장면 재생
		m_scene_manager.Play();

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
				

		// 월드 좌표계 그리기
		m_world_coordinates.Draw();
		

		////////////////////////////////////////////////////////////////////
		// UI 좌표계 그리기

		shader_UI.Bind();
		texture1.Bind(0);

		UI_transform.GetPos().x = +0.7f;
		UI_transform.GetPos().y = -0.7f;

		UI_transform.SetRot(camera.GetRot());

		shader_UI.Update(UI_transform, camera);
		m_UI_coordinates.Draw(5.0f);

		////////////////////////////////////////////////////////////////////

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		glDepthFunc(GL_LEQUAL);
		skyboxShader.Bind();
		skyboxTexture.Bind(0);
		skyboxMesh.Draw();
		skyboxShader.Update(world_transform, camera);
		glDepthFunc(GL_LESS);

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		
		display.Update();	// 화면갱신
	}
}

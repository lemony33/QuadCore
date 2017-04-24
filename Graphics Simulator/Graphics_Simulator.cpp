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
	Mesh SphereMesh("../media/shape/Sphere.obj");
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
	Texture SlimeTexture("../media/res/slime.jpg");
	Texture JupiterTexture("../media/res/Jupiter.jpg");
	Texture EarthTexture("../media/res/earth.jpg");
	Texture MoonTexture("../media/res/moon.jpg");
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

	// Draw Map 새로 추가된 부분
	DrawMap dMap(camera);
	dMap.SetProperty(100, 1.0f, glm::vec4(0.7f, 0.7f, 0.7f, 3.0f));


	// MS - 0420 - 좌표계 그리기
	
	////glm::mat4 view_matrix = camera.GetViewMatrix();	// 카메라 시점
	////camera.GetPos();
	//UI_transform.Init(camera.GetPos(), camera.GetForward());
	////glm::mat4 view_matrix = camera.GetViewMatrix();

	m_world_coordinates.Init(&world_transform, &camera, 50.0f);
	m_UI_coordinates.Init_UI(&UI_transform, &camera, 0.1f);
	//m_UI_coordinates.Init(&UI_transform, &camera, 10.0f);

	Coordinates coor_model_1;
	Coordinates coor_model_2;
	Coordinates coor_model_3;
	coor_model_1.Init(&transform1, &camera);
	coor_model_2.Init(&transform2, &camera);
	coor_model_3.Init(&transform3, &camera);

	scene.Init(&camera);

	float counter = 0.0f;

	
	

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
		
		//### 맵 그리기
		dMap.DrawPlane();					// Draw Map

		//### 시나리오별 장면 재생
		scene.Play();

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		///
		float delim = 0.7;


		///
		shader1.Bind();		
		texture1.Bind(0);
		//Texture::Reset();		// 텍스쳐 제거하는 방법

		transform1.SetPos(glm::vec3(0, 0, 0));
		transform1.SetPos(glm::vec3(1.1, 1.1, 0));

		transform1.GetPos().y += delim * sinf(counter);
		transform1.GetPos().x += delim * cosf(counter);
		transform1.GetRot().y = counter * 0.5f;
		transform1.GetRot().x = counter * 0.3f;
		shader1.Update(transform1, camera);		
		mesh1.Draw();
		coor_model_1.Draw();


		///
		shader1.Bind();
		texture1.Bind(0);

		transform2.SetPos(glm::vec3(-1.1, 0, 0));

		transform2.GetRot().y = counter * 0.5f;
		transform2.GetRot().x = counter * 0.3f;
		transform2.GetPos().y += delim * cosf(counter);
		transform2.GetPos().x += delim * sinf(counter);

		shader1.Update(transform2, camera);
		mesh1.Draw();
		coor_model_2.Draw();


		


		///
		shader1.Bind();
		texture1.Bind(0);

		float r = 3.0f;
		transform3.SetPos(glm::vec3(-r / 2.0f, 0, 0));
		transform3.GetPos().x += sinf(counter) * r;
		transform3.GetPos().y += cosf(counter) * r;

		transform3.GetRot().y = counter * 0.9f;
		transform3.GetRot().x = counter * 0.7f;

		//transform3.GetPos().z += tanf(counter) * r;
		shader1.Update(transform3, camera);
		mesh3.Draw();
		coor_model_3.Draw();
		

		// 월드 좌표계 그리기
		m_world_coordinates.Draw();

		//********************
		// UI 좌표계 그리기
		//********************


		////////////////////////////////////////////////////////////////////

		shader_UI.Bind();
		texture1.Bind(0);

		//glm::vec3 cur_pos = { 0.1,0.1,-1 };
		//UI_transform.Init(cur_pos);
		//UI_transform.Init(glm::vec3(0, 0, -3));

		UI_transform.GetPos().x = +0.7f;
		UI_transform.GetPos().y = -0.7f;


		//UI_transform.GetRot().y = camera.GetForward().x;

		///UI_transform.GetRot().x = camera.GetForward().x + camera.GetUpward();
		///UI_transform.SetRot();
		//UI_transform.GetRot().x = camera.GetForward().y;
		//UI_transform.GetRot().y = -camera.GetForward().x;
		//UI_transform.GetRot().z = camera.GetUpward().x;
		///UI_transform.GetRot().z = camera.GetForward().z;
		///UI_transform.SetRot(camera.GetUpward());
		
		//UI_transform.SetRot(glm::vec3(0, 0, camera.GetSide().y));
		//UI_transform.SetRot(glm::vec3(0, camera.GetForward().x, 0));

		/* 단순계산중 (회전축이 겹치면 오류발생)
		Rot_X_axis : +y축과 up 벡터의 사잇각
		Rot_Y_axis : -z축과 forward 벡터의 사잇각
		Rot_Z_axis : +x축과 side 벡터의 사잇각
		*/
		/*glm::vec3 cam_rot = {
			glm::acos(glm::dot(glm::vec3(0,+1,0), camera.GetUpward())),
			glm::acos(glm::dot(glm::vec3(0,0,-1), camera.GetForward())),	
			glm::acos(glm::dot(glm::vec3(+1,0,0), camera.GetSide())),
		};*/
		//// up-z : 음수일떄 정상동작, 양수일때 반대로 움직임
		//if (camera.GetUpward().z > 0)
		//	cam_rot.x = -cam_rot.x;

		//// forward-x : 음수일때 정상동장, 양수일때 반대로 움직임
		//if (camera.GetForward().x > 0)
		//	cam_rot.y = -cam_rot.y;

		//// side-y : 음수일때 정상동장, 양수일때 반대로 움직임
		//if (camera.GetSide().y > 0)
		//	cam_rot.z = -cam_rot.z;		

		//UI_transform.SetRot(cam_rot);
		UI_transform.SetRot(camera.GetRot());

		//printf(" cam_rot (%f,%f,%f),   ", cam_rot.x, cam_rot.y, cam_rot.z);
		//printf(" up (%f,%f,%f)\n", camera.GetUpward().x, camera.GetUpward().y, camera.GetUpward().z);
		//printf(" forward (%f,%f,%f)\n", camera.GetForward().x, camera.GetForward().y, camera.GetForward().z);
		//printf(" side (%f,%f,%f)\n", camera.GetSide().x, camera.GetSide().y, camera.GetSide().z);

		/*float speed = 0.1f;
		UI_transform.GetRot().x += sinCounter * speed;
		UI_transform.GetRot().y += cosCounter * speed;
		UI_transform.GetRot().z += sinCounter * speed;*/

		shader_UI.Update(UI_transform, camera);
		//mesh3.Draw();
		m_UI_coordinates.Draw(5.0f);

		//printf("UI_POS( %.2f, %.2f, %.2f ), ", UI_transform.GetPos().x, UI_transform.GetPos().y, UI_transform.GetPos().z);
		//printf("FORWARD( %.2f, %.2f, %.2f ), ", camera.GetForward().x, camera.GetForward().y, camera.GetForward().z);
		//printf("UP( %.2f, %.2f, %.2f ) \n", camera.GetUpward().x, camera.GetUpward().y, camera.GetUpward().z);
		///shader1.Update(UI_transform, camera);

	

		//mesh3.Draw();

		////////////////////////////////////////////////////////////////////

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//*************
		Transform mainSphere(glm::vec3(5 * sinf(counter/10), 0, 5 * cosf(counter / 10)),
			glm::vec3(counter / 5, counter/5, 1.0f),
			glm::vec3(5.0f, 5.0f, 5.0f)
			);
		
		for (int i = 0; i < 28; i++)
		{
			/*Transform subSphere(glm::vec3(mainSphere.GetPos().x + 5 * sinf((counter + i * 0.1f) / 5) * cosf(-(counter + i * 0.1f) / 5),
										mainSphere.GetPos().y + 5 * sinf(-(counter + i * 0.1f) / 5),
										mainSphere.GetPos().z + 5 * cosf((counter + i * 0.1f) / 5) * cosf(-(counter + i * 0.1f) / 5)),
				glm::vec3(),
				glm::vec3(0.5f, 0.5f, 0.5f)
			);*/
			/*Transform subSphere(glm::vec3(mainSphere.GetPos().x + 5 * sinf(counter + i * 1.2f/5) * sinf((counter + i * 3.1f)/5),
				mainSphere.GetPos().y + 5 * cosf((counter + i * 3.1f)/5),
				mainSphere.GetPos().z + 5 * cosf(counter + i * 1.2f /5) * sinf((counter + i * 3.1f)/5)),
				glm::vec3(),
				glm::vec3(0.5f, 0.5f, 0.5f)
			);*/
			Transform subSphere(glm::vec3(mainSphere.GetPos().x + 5 * sinf(counter/5 + i * 1.2f / 5) * cosf(sinf(counter / (i + 1) + i * 3.1f) / 10.0f),
				mainSphere.GetPos().y + 5 * sinf(sinf(counter / (i + 1) + i * 3.1f)/10.0f),
				mainSphere.GetPos().z + 5 * cosf(counter/5 + i * 1.2f / 5) * cosf(sinf(counter / (i + 1) + i * 3.1f) / 10.0f)
				),
				glm::vec3(),
				glm::vec3(0.5f, 0.5f, 0.5f)
			);
			shader1.Bind();
			MoonTexture.Bind(0);
			shader1.Update(subSphere, camera);
			SphereMesh.Draw();
		}

		shader1.Bind();
		EarthTexture.Bind(0);
		shader1.Update(mainSphere, camera);
		SphereMesh.Draw();
		
		Transform slimeTransform(glm::vec3(0,0,-2),
			glm::vec3(),
			glm::vec3(1.0f + 0.2f * sinf(counter * 2), 1.0f + 0.2f * cosf(counter * 2), 1.0f + 0.2f * sinf(counter * 2)));
		shader1.Bind();
		SlimeTexture.Bind(0);
		shader1.Update(slimeTransform, camera);
		SphereMesh.Draw();

		for (int i = 0; i < 128; i++)
		{
			Transform subSphere(glm::vec3(5 * sinf((counter + i * 0.2f) / 5) * cosf(-(counter + i * 0.2f) / 5),
			5 * sinf(-(counter + i * 0.2f) / 5),
			5 * cosf((counter + i * 0.2f) / 5) * cosf(-(counter + i * 0.2f) / 5)),
			glm::vec3(),
			glm::vec3(0.5f, 0.5f, 0.5f)
			);
			glassShader.Bind();
			skyboxTexture.Bind(0);
			glassShader.Update(subSphere, camera);
			SphereMesh.Draw();

			if (i == 0)
			{
				Transform BarTransform((subSphere.GetPos() + glm::vec3(0, 0, 0)) / 2.0f,
					glm::vec3(-subSphere.GetPos().y / sqrtf(subSphere.GetPos().y * subSphere.GetPos().y + subSphere.GetPos().z * subSphere.GetPos().z),
						-subSphere.GetPos().z / sqrtf(subSphere.GetPos().x * subSphere.GetPos().x + subSphere.GetPos().z * subSphere.GetPos().z),
						-subSphere.GetPos().y / sqrtf(subSphere.GetPos().y * subSphere.GetPos().y + subSphere.GetPos().x * subSphere.GetPos().x)
					),
					glm::vec3(0.1f, 0.1f, 1.0f * glm::distance(subSphere.GetPos(), glm::vec3(0, 0, 0)))
				);
				shader1.Bind();
				texture1.Bind(0);
				shader1.Update(BarTransform, camera);
				mesh1.Draw();

			}
		}



		glDepthFunc(GL_LEQUAL);
		skyboxShader.Bind();
		skyboxTexture.Bind(0);
		skyboxMesh.Draw();
		skyboxShader.Update(world_transform, camera);
		glDepthFunc(GL_LESS);
		

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		
		display.Update();	// 화면갱신
		counter += 0.05f;	// 카운터 증가
	}
}

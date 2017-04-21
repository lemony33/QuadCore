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
	Vertex SkyBoxVerties[] = // 스카이박스 vertices
	{
		Vertex(glm::vec3(-100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(100.0f,  100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(100.0f,  100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(-100.0f,  100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),

		/*Vertex(glm::vec3(-100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(-100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),*/
		Vertex(glm::vec3(-100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(-100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),

		/*Vertex(glm::vec3(-100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f,  100.0f, -100.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),*/
		Vertex(glm::vec3(-100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f,  100.0f, -100.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),

		Vertex(glm::vec3(100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(100.0f,  100.0f, -100.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),

		/*Vertex(glm::vec3(-100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),*/
		Vertex(glm::vec3(-100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(100.0f, -100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),

		Vertex(glm::vec3(-100.0f,  100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(100.0f,  100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f,  100.0f,  100.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(-100.0f,  100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f))
	};
	unsigned int indices[] = {
		0,1,2, 2,3,0,   // 36 of indices
		0,3,4, 4,5,0,
		0,5,6, 6,1,0,
		1,6,7, 7,2,1,
		7,4,3, 3,2,7,
		4,7,6, 6,5,4
	}; // 스카이박스 indices
	// 1. Object
	Mesh mesh1("../media/shape/Cube.obj");
	//Mesh mesh1("../media/shape/Wedge.obj");
	//Mesh mesh1("../media/shape/CubeHollow.obj");
	Mesh mesh2("../media/shape/CubeHollow.obj");
	Mesh mesh3("../media/shape/Icosphere.obj");
	Mesh skyboxMesh(SkyBoxVerties, sizeof(SkyBoxVerties) / sizeof(SkyBoxVerties[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh nanosuitMesh("../media/objects/nanosuit_reflection/nanosuit.obj");

	// 2. Shader
	Shader shader1("../media/new_shader/basicShader_light");
	Shader shader2("../media/new_shader/basicShader_tex");
	//Shader shader1("../media/shaders/cubemaps/cubemaps");
	Shader skyboxShader("../media/shaders/cubemaps/skybox");
	Shader glassShader("../media/shaders/cubemaps/glass");
	Shader mirrorShader("../media/shaders/cubemaps/mirror");

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

	// Draw Map 새로 추가된 부분
	DrawMap dMap(camera);
	dMap.SetProperty(100, 1.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

	// MS - 0420 - 좌표계 그리기
	
	////glm::mat4 view_matrix = camera.GetViewMatrix();	// 카메라 시점
	////camera.GetPos();
	//UI_transform.Init(camera.GetPos(), camera.GetForward());
	////glm::mat4 view_matrix = camera.GetViewMatrix();

	m_world_coordinates.Init(&world_transform, &camera, 5.0f);
	m_UI_coordinates.Init(&UI_transform, &camera, 0.05f);

	Coordinates coor_model_1;
	Coordinates coor_model_2;
	Coordinates coor_model_3;
	coor_model_1.Init(&transform1, &camera);
	coor_model_2.Init(&transform2, &camera);
	coor_model_3.Init(&transform3, &camera);



	float counter = 0.0f;

	while (!display.IsClosed())
	{	
		float sinCounter = sinf(counter);	// sin counter
		float cosCounter = cosf(counter);	// cos counter

		display.UpdateWindowSize();	// 화면 갱신
		camera.Update(camera.GetPos(), 70.0f, display.GetWindowAspec(), 0.01F, 1000.0f);
				
		display.Clear(0.1f, 0.1f, 0.1f, 1.0f);	// 배경 초기화
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);	// 배경 초기화

		//display.Clear(0.3f, 0.3f, 0.3f, 1.0f);	// 배경 초기화
		
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		// Draw here
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		// MS - 0420 - 좌표계 그리기
		
		m_world_coordinates.Draw();

		glassShader.Bind();
		skyboxTexture.Bind(0);
		glassShader.Update(glassTrans, camera);
		nanosuitMesh.Draw();

		mirrorShader.Bind();
		skyboxTexture.Bind(0);
		mirrorShader.Update(mirrorTrans, camera);
		nanosuitMesh.Draw();

		/*UI_transform.Init(camera.GetPos());
		UI_transform.GetPos().x += camera.GetForawrd().x;
		UI_transform.GetPos().y += camera.GetForawrd().y;
		UI_transform.GetPos().z += camera.GetForawrd().z;
		m_UI_coordinates.Draw();*/

		


		// Draw Map 새로 추가된 부분
		dMap.DrawPlane();


		m_shape_manager;

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
		


		//**************

		shader1.Bind();
		texture1.Bind(0);

		//world_transform.GetPos();
		

		//UI_transform.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

		glm::vec3 cur_pos = { camera.GetPos().x, camera.GetPos().y, camera.GetPos().z };
		//glm::vec3 cur_pos = { camera.GetPos().x, camera.GetPos().y, camera.GetPos().z};
		UI_transform.Init(cur_pos);
		//UI_transform.Init(cur_pos, glm::vec3(camera.GetForward().x, camera.GetForward().y, camera.GetForward().z));
		//UI_transform.GetRot().x += camera.GetForward().x;
		//UI_transform.GetRot().y += camera.GetForward().y;
		//UI_transform.GetRot().z += camera.GetForward().z;

		UI_transform.GetPos().x += camera.GetForward().x * .3+.1;
		UI_transform.GetPos().y += camera.GetForward().y * .3+.1;
		UI_transform.GetPos().z += camera.GetForward().z * .3;

		//UI_transform.GetPos().x += .0;
		//UI_transform.GetPos().y += .0;
		//UI_transform.GetPos().z += camera.GetForward().z * .3;
		////UI_transform.SetRot(camera.GetRot());

		printf("UI_POS( %.2f, %.2f, %.2f ), ", UI_transform.GetPos().x, UI_transform.GetPos().y, UI_transform.GetPos().z);
		printf("FORWARD( %.2f, %.2f, %.2f ) \n", camera.GetForward().x, camera.GetForward().y, camera.GetForward().z);
		//shader1.Update(UI_transform, camera);


		
		//mesh3.Draw();
		m_UI_coordinates.Draw(3.0f);

		//*************
		glDepthFunc(GL_LEQUAL);
		skyboxShader.Bind();
		skyboxTexture.Bind(0);
		skyboxMesh.Draw();
		skyboxShader.Update(world_transform, camera);
		glDepthFunc(GL_LESS);


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		
		display.Update();	// 화면갱신
		counter += 0.05f;	// 카운터 증가
	}
}

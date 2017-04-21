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
	Vertex SkyBoxVerties[] =
	{
		Vertex(glm::vec3(- 100.0f, -100.0f, -100.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
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
	Vertex CubeVerties[] =
	{
		/*Vertex(glm::vec3(-5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(-5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(-5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),*/
		Vertex(glm::vec3(-5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(-5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(-5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),

		Vertex(glm::vec3(-5.0f, -5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(5.0f, -5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(-5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(-5.0f, -5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		
		Vertex(glm::vec3(-5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-5.0f, -5.0f,  5.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),

		/*Vertex(glm::vec3(5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(5.0f, -5.0f,  5.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),*/
		Vertex(glm::vec3(5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(5.0f, -5.0f,  5.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),

		Vertex(glm::vec3(-5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(5.0f, -5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(5.0f, -5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(-5.0f, -5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(-5.0f, -5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),

		/*Vertex(glm::vec3(-5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(-5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(-5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f))*/
		Vertex(glm::vec3(-5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(-5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(5.0f,  5.0f,  5.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f)),
		Vertex(glm::vec3(-5.0f,  5.0f, -5.0f),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f,  0.0f))
	};
	unsigned int indices[] = { 
		0,1,2, 2,3,0,   // 36 of indices
		0,3,4, 4,5,0,
		0,5,6, 6,1,0,
		1,6,7, 7,2,1,
		7,4,3, 3,2,7,
		4,7,6, 6,5,4
	};
	// 1. Object
	//Mesh mesh1("../media/shape/Cube.obj");
	Mesh mesh1(SkyBoxVerties, sizeof(SkyBoxVerties)/sizeof(SkyBoxVerties[0]),indices, sizeof(indices) / sizeof(indices[0]));
	//Mesh mesh2("../media/shape/Cube.obj");
	Mesh mesh2(CubeVerties, sizeof(SkyBoxVerties) / sizeof(SkyBoxVerties[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh mesh3("../media/objects/nanosuit_reflection/nanosuit.obj"); 
	Mesh mesh4("../media/shape/Sphere.obj");

	// 2. Shader
	//Shader shader1("../media/new_shader/basicShader_light");
	//Shader shader2("../media/new_shader/basicShader_tex");
	Shader shader1("../media/shaders/cubemaps/cubemaps");
	Shader shader2("../media/shaders/cubemaps/skybox");
	Shader glassshader("../media/shaders/cubemaps/glass");
	Shader mirrorshader("../media/shaders/cubemaps/mirror");
	
	//3. Texture
	Texture texture1("../media/res/bricks.jpg");
	Texture texture2("../media/skyblue.jpg");

	//--- 스카이박스들어간다
	std::vector<std::string> faces;
	faces.push_back("../media/textures/skybox/right.jpg");
	faces.push_back("../media/textures/skybox/left.jpg");
	faces.push_back("../media/textures/skybox/top.jpg");
	faces.push_back("../media/textures/skybox/bottom.jpg");
	faces.push_back("../media/textures/skybox/back.jpg");
	faces.push_back("../media/textures/skybox/front.jpg");

	Texture skyboxTexture(faces);
	//---반대로 가 봅시다
	std::vector<std::string> faces2;
	faces2.push_back("../media/textures/skybox/left.jpg");
	faces2.push_back("../media/textures/skybox/right.jpg");
	faces2.push_back("../media/textures/skybox/bottom.jpg");
	faces2.push_back("../media/textures/skybox/top.jpg");
	faces2.push_back("../media/textures/skybox/front.jpg");
	faces2.push_back("../media/textures/skybox/back.jpg");

	Texture reflectTexture(faces2);
	//texture2.Reset();
	

	//4. Transform
	Transform worldCoordinate;
	Transform transform1;
	Transform transform2;
	Transform Bullet;
	Transform glassTrans(glm::vec3(10.0, 0, 0));
	Transform mirrorTrans(glm::vec3(-10.0, 0, 0));
	
	
	//5. Camera
	float aspec = (float)width_window / (float)height_window;
	Camera camera(glm::vec3(0, 0, 10), 70.0f, aspec, 0.01F, 1000.0f);

	// Controls (Mouse / Keyboard)
	Controls controls(display.GetWindow());
	Controls controller(controls, camera, Bullet);

	// Draw Map 새로 추가된 부분
	DrawMap dMap(camera);
	dMap.SetProperty(100, 1.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

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

		// Draw Map 새로 추가된 부분
		dMap.DrawPlane();


		m_shape_manager;
		if (camera.fire == false)Bullet = camera.GetPos();
		else
		{
			Bullet.GetPos() += camera.GetForward();
		}
		if (Bullet.GetPos().x >= 100.0 || Bullet.GetPos().y >= 100.0 || Bullet.GetPos().z >= 100.0
			|| Bullet.GetPos().x <= -100.0 || Bullet.GetPos().y <= -100.0 || Bullet.GetPos().z <= -100.0)
		{
			Bullet = camera.GetPos();
			camera.fire = false;
		}

		glassshader.Bind();		
		//reflectTexture.Bind(0);
		skyboxTexture.Bind(0);
		glassshader.Update(glassTrans, camera);
		mesh3.Draw();

		mirrorshader.Bind();
		//reflectTexture.Bind(0);
		skyboxTexture.Bind(0);
		mirrorshader.Update(mirrorTrans, camera);
		mesh3.Draw();

		shader1.Bind();
		//reflectTexture.Bind(0);
		skyboxTexture.Bind(0);
		shader1.Update(Bullet, camera);
		mesh4.Draw();
		
		
		glDepthFunc(GL_LEQUAL);
		shader2.Bind();
		skyboxTexture.Bind(0);
		mesh1.Draw();
		shader2.Update(Transform(camera.GetPos()), camera);
		glDepthFunc(GL_LESS);
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		
		display.Update();	// 화면갱신
		counter += 0.05f;	// 카운터 증가
		
	}
}

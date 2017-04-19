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
	Vertex CubeVerties[] =
	{
		Vertex(glm::vec3(- 500.0f, -500.0f, -500.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(500.0f, -500.0f, -500.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(500.0f,  500.0f, -500.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(500.0f,  500.0f, -500.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(-500.0f,  500.0f, -500.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),
		Vertex(glm::vec3(-500.0f, -500.0f, -500.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),

		Vertex(glm::vec3(-500.0f, -500.0f,  500.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(500.0f, -500.0f,  500.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(500.0f,  500.0f,  500.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(500.0f,  500.0f,  500.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(-500.0f,  500.0f,  500.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),
		Vertex(glm::vec3(-500.0f, -500.0f,  500.0f),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, 1.0f)),

		Vertex(glm::vec3(-500.0f,  500.0f,  500.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-500.0f,  500.0f, -500.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-500.0f, -500.0f, -500.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-500.0f, -500.0f, -500.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-500.0f, -500.0f,  500.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-500.0f,  500.0f,  500.0f),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f,  0.0f)),

		Vertex(glm::vec3(500.0f,  500.0f,  500.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(500.0f,  500.0f, -500.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(500.0f, -500.0f, -500.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(500.0f, -500.0f, -500.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(500.0f, -500.0f,  500.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(500.0f,  500.0f,  500.0f),glm::vec2(0,0),glm::vec3(1.0f,  0.0f,  0.0f)),

		Vertex(glm::vec3(-500.0f, -500.0f, -500.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(500.0f, -500.0f, -500.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(500.0f, -500.0f,  500.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(500.0f, -500.0f,  500.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(-500.0f, -500.0f,  500.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(-500.0f, -500.0f, -500.0f),glm::vec2(0,0),glm::vec3(0.0f, -1.0f,  0.0f)),

		Vertex(glm::vec3(-500.0f,  500.0f, -500.0f),glm::vec2(0,0),glm::vec3(0.0f,  1.0f,  0.0f)),
		Vertex(glm::vec3(500.0f,  500.0f, -500.0f),glm::vec2(0,0),glm::vec3(0.0f,  1.0f,  0.0f)),
		Vertex(glm::vec3(500.0f,  500.0f,  500.0f),glm::vec2(0,0),glm::vec3(0.0f,  1.0f,  0.0f)),
		Vertex(glm::vec3(500.0f,  500.0f,  500.0f),glm::vec2(0,0),glm::vec3(0.0f,  1.0f,  0.0f)),
		Vertex(glm::vec3(-500.0f,  500.0f,  500.0f),glm::vec2(0,0),glm::vec3(0.0f,  1.0f,  0.0f)),
		Vertex(glm::vec3(-500.0f,  500.0f, -500.0f),glm::vec2(0,0),glm::vec3(0.0f,  1.0f,  0.0f))
	};
	unsigned int indices[] = { 0, 1, 2,
		0, 2, 3,

		6, 5, 4,
		7, 6, 4,

		10, 9, 8,
		11, 10, 8,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		22, 21, 20,
		23, 22, 20
	};
	// 1. Object
	//Mesh mesh1("../media/shape/Cube.obj");
	Mesh mesh1(CubeVerties, sizeof(CubeVerties)/sizeof(CubeVerties[0]),indices, sizeof(indices) / sizeof(indices[0]));
	Mesh mesh2("../media/shape/Cube.obj");

	// 2. Shader
	//Shader shader1("../media/new_shader/basicShader_light");
	//Shader shader2("../media/new_shader/basicShader_tex");
	Shader shader1("../media/shaders/cubemaps/cubemaps");
	Shader shader2("../media/shaders/cubemaps/skybox");
	
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
	
	//texture2.Reset();
	

	//4. Transform
	Transform worldCoordinate;
	Transform transform1;
	Transform transform2;
	Transform transform3;
	
	
	//5. Camera
	float aspec = (float)width_window / (float)height_window;
	Camera camera(glm::vec3(0, 0, 10), 70.0f, aspec, 0.01F, 1000.0f);

	// Controls (Mouse / Keyboard)
	Controls controls(display.GetWindow());
	Controls controller(controls, camera, worldCoordinate);

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



		shader1.Bind();		
		skyboxTexture.Bind(0);
		//Texture::Reset();

		/*transform1.SetPos(glm::vec3(0, 0, 0));
		transform1.SetPos(glm::vec3(1.1, 1.1, 0));
		transform1.GetRot().y = counter * 0.5f;
		transform1.GetRot().x = counter * 0.3f;*/
		shader1.Update(transform1, camera);		
		mesh1.Draw();

		glDepthFunc(GL_LEQUAL);
		shader2.Bind();
		skyboxTexture.Bind(0);
		mesh2.Draw();
		glDepthFunc(GL_LESS);
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		
		display.Update();	// 화면갱신
		counter += 0.05f;	// 카운터 증가
	}
}

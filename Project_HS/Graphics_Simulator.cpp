#include "Graphics_Simulator.h"

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

	// 2. Shader
	Shader shader1("../media/new_shader/basicShader_tex");
	Shader shader2("../media/new_shader/basicShader_tex");
	
	//3. Texture
	Texture texture1("../media/res/bricks.jpg");
	Texture texture2("../media/skyblue.jpg");
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

	// MS - 0420 - 좌표계 그리기
	m_coordinates.Init(&worldCoordinate, &camera, 5.0f);

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
		m_coordinates.Draw();


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
		transform1.SetPos(glm::vec3(0, 0.5, 0));

		shader1.Update(transform1, camera);		
		mesh1.Draw();
		coor_model_1.Draw();


		///
		shader1.Bind();
		texture1.Bind(0);

		transform2.SetPos(glm::vec3(0, 0.5, -2));

		shader1.Update(transform2, camera);
		mesh1.Draw();
		coor_model_2.Draw();



		///
		shader1.Bind();
		texture1.Bind(0);

		float r = 3.0f;
		shader1.Update(transform3, camera);
		


		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		
		display.Update();	// 화면갱신
		counter += 0.05f;	// 카운터 증가
	}
}

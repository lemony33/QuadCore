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

	// 1. Object	// 도형모양
	Mesh mesh1("../media/shape/Cube.obj");
	//Mesh mesh1("../media/shape/Wedge.obj");
	//Mesh mesh1("../media/shape/CubeHollow.obj");
	Mesh mesh2("../media/shape/CubeHollow.obj");

	Mesh mesh3("../media/shape/Icosphere.obj");

	// 2. Shader	// vs, fs
	Shader shader1("../media/new_shader/basicShader_light");
	Shader shader2("../media/new_shader/basicShader_tex");

	//3. Texture	// 도형배경
	Texture texture1("../media/res/bricks.jpg");
	Texture texture2("../media/skyblue.jpg");
	Texture texture3("../media/image2.png");

	//texture2.Reset();


	Vertex vertices[] = {
		Vertex(glm::vec3(0.5, 0.5,  0.0),	glm::vec2(1.0,1.0) , glm::vec3(0,0,1)),	// 모양 점위치 / 모양 배경위치(TopRight, BottomRight, BottomLeft(원점), TopLeft) / 색깔
		Vertex(glm::vec3(0.5,  -0.5,  0.0),	glm::vec2(1.0,0.0) , glm::vec3(0,0,1)),
		Vertex(glm::vec3(-0.5, -0.5,  0.0),	glm::vec2(0.0,0.0) , glm::vec3(0,0,1)),
		Vertex(glm::vec3(-0.5, 0.5,  0.0),	glm::vec2(0.0,1.0) , glm::vec3(0,0,1)),
	};
	unsigned int indices[] = {
		2,1,0,
		3,2,0,
	};
	Mesh mesh_vertices(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));


	//4. Transform
	Transform worldCoordinate;
	Transform transform1;
	Transform transform2;
	Transform transform3;
	Transform transform_vertice;


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


												//Shader s("../media/MapShader");
												//s.SetLineColor(glm::vec4(1.0, 0, 0, 1));
												//glLineWidth(3);

												//s.Bind();
												//s.Update(worldCoordinate, camera);
												//mesh.DrawLines();




												//worldCoordinate.GetPos().z = -2;
												//worldCoordinate.GetRot().x += 0.01;
		shader1.Update(worldCoordinate, camera);
		texture3.Bind(0);
		mesh_vertices.Draw();







		// Draw Map 새로 추가된 부분
		dMap.DrawPlane();


		m_shape_manager;



		shader1.Bind();
		texture1.Bind(0);
		//Texture::Reset();

		float delim = 0.7;

		transform1.SetPos(glm::vec3(0, 0, 0));
		transform1.SetPos(glm::vec3(1.1, 1.1, 0));
		transform1.GetRot().y = counter * 0.5f;
		transform1.GetRot().x = counter * 0.3f;

		transform1.GetPos().y += delim * sinf(counter);
		transform1.GetPos().x += delim * cosf(counter);

		shader1.Update(transform1, camera);
		mesh1.Draw();




		transform2.SetPos(glm::vec3(-1.1, 0, 0));

		transform2.GetRot().y = counter * 0.5f;
		transform2.GetRot().x = counter * 0.3f;

		transform2.GetPos().y += delim * cosf(counter);
		transform2.GetPos().x += delim * sinf(counter);

		shader1.Update(transform2, camera);
		mesh1.Draw();


		//float r = 3.0f;
		//transform3.SetPos(glm::vec3(-r/2.0f, 0, 0));
		//transform3.GetPos().x += sinf(counter) * r;
		//transform3.GetPos().y += cosf(counter) * r;	

		//transform3.GetRot().y = counter * 0.9f;
		//transform3.GetRot().x = counter * 0.7f;

		////transform3.GetPos().z += tanf(counter) * r;
		//shader1.Update(transform3, camera);
		//mesh3.Draw();

		/*
		transform2.SetPos(glm::vec3(-1.1, 0, 0));
		shader1.Update(transform2, camera);
		mesh1.Draw();

		transform3.SetPos(glm::vec3(1.1, 0, 0));
		shader1.Update(transform3, camera);
		mesh1.Draw();



		transform1.SetPos(glm::vec3(0, 1.1, 0));
		shader1.Update(transform1, camera);
		mesh1.Draw();

		transform2.SetPos(glm::vec3(-1.1, 1.1, 0));
		shader1.Update(transform2, camera);
		mesh1.Draw();

		transform3.SetPos(glm::vec3(1.1, 1.1, 0));
		shader1.Update(transform3, camera);
		mesh1.Draw();


		transform1.SetPos(glm::vec3(0, -1.1, 0));
		shader1.Update(transform1, camera);
		mesh1.Draw();

		transform2.SetPos(glm::vec3(-1.1, -1.1, 0));
		shader1.Update(transform2, camera);
		mesh1.Draw();

		transform3.SetPos(glm::vec3(1.1, -1.1, 0));
		shader1.Update(transform3, camera);
		mesh1.Draw();
		*/

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		display.Update();	// 화면갱신
		counter += 0.005f;	// 카운터 증가
	}
}

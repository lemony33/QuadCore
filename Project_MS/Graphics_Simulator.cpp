#include "Graphics_Simulator.h"

#include "enum_type.h"

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
	Shader shader1("../media/new_shader/basicShader_light");
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



	m_coordinates.Init(&worldCoordinate, &camera);

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

	/*	float coordinate_length = 3.0f;

		Vertex vertex_0 = Vertex(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(), glm::vec3());
		Vertex vertex_x = Vertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(), glm::vec3());
		Vertex vertex_y = Vertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(), glm::vec3());
		Vertex vertex_z = Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(), glm::vec3());

		vertex_x.GetPos()->x *= coordinate_length;
		vertex_y.GetPos()->y *= coordinate_length;
		vertex_z.GetPos()->z *= coordinate_length;

		unsigned int indices[] = { 0, 1, };
		Vertex vertices_x[] = { vertex_0, vertex_x };
		Vertex vertices_y[] = { vertex_0, vertex_y };
		Vertex vertices_z[] = { vertex_0, vertex_z };

		Mesh coordinate_x(vertices_x, sizeof(vertices_x) / sizeof(vertices_x[0]), indices, sizeof(indices) / sizeof(indices[0]));
		Mesh coordinate_y(vertices_y, sizeof(vertices_y) / sizeof(vertices_x[0]), indices, sizeof(indices) / sizeof(indices[0]));
		Mesh coordinate_z(vertices_z, sizeof(vertices_z) / sizeof(vertices_x[0]), indices, sizeof(indices) / sizeof(indices[0]));

		Shader s("../media/MapShader");		
		s.Bind();
		s.Update(worldCoordinate, camera);

		glLineWidth(3);
		s.SetLineColor(glm::vec4(1.0, 0.0, 0.0, 1.0));	coordinate_x.DrawLines();
		s.SetLineColor(glm::vec4(0.0, 1.0, 0.0, 1.0));	coordinate_y.DrawLines();
		s.SetLineColor(glm::vec4(0.0, 0.0, 1.0, 1.0));	coordinate_z.DrawLines();*/

		m_coordinates.Draw();
		

		//worldCoordinate.GetPos().z = -2;
		//worldCoordinate.GetRot().x += 0.01;
		//shader1.Update(worldCoordinate, camera);
		//mesh.Draw();


		




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
		transform3.SetPos(glm::vec3(-r/2.0f, 0, 0));
		transform3.GetPos().x += sinf(counter) * r;
		transform3.GetPos().y += cosf(counter) * r;	

		transform3.GetRot().y = counter * 0.9f;
		transform3.GetRot().x = counter * 0.7f;

		//transform3.GetPos().z += tanf(counter) * r;
		shader1.Update(transform3, camera);
		mesh3.Draw();
		coor_model_3.Draw();

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
		counter += 0.05f;	// 카운터 증가
	}
}

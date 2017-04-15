#include "Graphics_Simulator.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

#include "Controls.h"


QuadCore::Graphics_Simulator::Graphics_Simulator()
	: display(width_window, height_window, "Graphics Simulator - QuadCore")
{
}


QuadCore::Graphics_Simulator::~Graphics_Simulator()
{
}


void QuadCore::Graphics_Simulator::Run()
{
	//// mesh 삼각형 도형그려주기
	Vertex vertices[] = {
							Vertex(	glm::vec3(-0.5, -0.5,  0.0),	glm::vec2(0.0,0.0)	),
							Vertex(	glm::vec3( 0.0,  0.5,  0.0),	glm::vec2(0.0,1.0)	),
							Vertex(	glm::vec3( 0.5, -0.5,  0.0),	glm::vec2(1.0,1.0)	),
							Vertex(	glm::vec3( 0.0, -1.5,  0.0),	glm::vec2(0.0,1.0)	),
						};
	unsigned int indices[] = {
								2,1,0,
								3,2,0,
							};
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	// *.obj 파일로딩

	Mesh mesh1("../media/shape/Wedge.obj");
	Mesh mesh2("../media/shape/CubeHollow.obj");
	//1. shader도형색깔	
	//Shader shader("../media/MakePlaneShader");
	//Shader shader("../media/res/basicShader");
	Shader shader("../media/basicShader_light");
	Shader shader2("../media/basicShader_tex");
	//3. Texture
	Texture texture("../media/res/bricks.jpg");
	Texture texture2("../media/skyblue.jpg");
	//4. Transform
	Transform transform;
	float counter = 0.0f;
	//5. Camera

	int width = width_window;	//**
	int height = height_window;	//**
	display.GetFrameBufferSize(&width, &height);	//**
	//Camera camera(glm::vec3(0, 0, 5), 70.0f, (float)width / (float)height, 0.01F, 1000.0f);
	Camera camera(glm::vec3(0, 0, 5), 70.0f, (float)width_window / (float)height_window, 0.01F, 1000.0f);

	Controls controls(display.GetWindow());

	while (!display.IsClosed())
	{
		//display 바탕화면
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform.GetPos().x = sinf(counter);
		transform.GetPos().y = sinf(counter);	//
		transform.GetPos().z = cosf(counter);
		transform.GetRot().x = counter * 0.5;
		transform.GetRot().y = counter * 0.5;
		transform.GetRot().z = counter * 0.5;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		transform.GetPos().x -= 2.5;
		transform.SetScale(glm::vec3(1, 1, 1));
		shader.Update(transform, camera);
		mesh1.Draw();

		shader2.Bind();
		texture2.Bind(0);
		//transform.GetPos().x += 1.5;
		transform.GetPos().x -= 1.5;
		//transform.GetPos().z += 1.5;
		//transform.SetScale(glm::vec3(3,0.5,1));
		transform.SetScale(glm::vec3(1, 1, 1));
		shader.Update(transform, camera);		
		mesh2.Draw();


		//shader.Bind();
		//texture.Bind(0);
		//transform.SetScale(glm::vec3(1, 1, 1));
		//transform.GetPos().y -= 10.0;

		shader.Bind();
		texture.Bind(0);
		transform.GetPos().x += 2.5;
		transform.SetScale(glm::vec3(1, 1, 1));
		shader.Update(transform, camera);

		

		display.Update();
		counter += 0.05f;
	}
}

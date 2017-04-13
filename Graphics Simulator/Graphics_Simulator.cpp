#include "Graphics_Simulator.h"


#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"



QuadCore::Graphics_Simulator::Graphics_Simulator()
	: display(width_window, height_window, "Graphics Simulator - QuadCore")
{
}


QuadCore::Graphics_Simulator::~Graphics_Simulator()
{
}


void QuadCore::Graphics_Simulator::Run()
{
	//Display display(width_window, height_window, "Graphics Simulator - QuadCore");

	//2. mesh 삼각형 도형그려주기
	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0,0.0)),
		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5,1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0,0.0)) };

	unsigned int indices[] = { 0,1,2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	//Mesh mesh2("./object/magnolia.obj");
	Mesh mesh2("../media/shape/cube.obj");
	//1. shader도형색깔
	Shader shader("../media/res/basicShader");
	//3. Texture
	Texture texture("../media/res/bricks.jpg");
	//4. Transform
	Transform transform;
	float counter = 0.0f;
	//5. Camera
	Camera camera(glm::vec3(0, 0, -20), 70.0f, (float)width_window / (float)height_window, 0.01F, 1000.0f);

	while (!display.IsClosed())
	{
		//display 바탕화면
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform.GetPos().x = sinf(counter);
		transform.GetPos().z = cosf(counter);
		transform.GetRot().x = counter * 0.5;
		transform.GetRot().y = counter * 0.5;
		transform.GetRot().z = counter * 0.5;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh2.Draw();

		display.Update();
		counter += 0.1f;
	}
}
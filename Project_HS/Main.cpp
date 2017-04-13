//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include <iostream>
#include <GLEW-2.0.0_x64/GL/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	unsigned int indices[] =
	{
		5, 7, 6,
		5, 6, 4
	};

	Vertex vertices[] =
	{
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f,0.0f)),	// Vertices[0]
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f,0.0f)),		// Vertices[1]
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f,0.0f)),		// Vertices[2]
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(0.0f,0.0f)),		// Vertices[3]
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.0f,0.0f)),		// Vertices[4]
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.0f,0.0f)),		// Vertices[5]
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f,0.0f)),		// Vertices[6]
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f,0.0f)),		// Vertices[7]
	};

	Display display(WIDTH, HEIGHT, "Hello World!");

	Mesh mesh_normal(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Shader shader("./res/MakePlaneShader");

	//Mesh mesh_obj("./res/monkey3.obj");
	//Shader shader("./res/basicShader");

	Camera camera(glm::vec3(0.0f, 0.0f, -10.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Texture texture("./res/bricks.jpg");
	Transform transform;

	float counter = 0.0f;
	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);
		//float sinCounter = sinf(45.0f);
		//float cosCounter = cosf(45.0f);

		transform.GetPos().x = sinCounter;
		transform.GetPos().y = cosCounter;
		transform.GetRot().x = counter * 1.0f;
		transform.GetRot().y = counter * 1.0f;
		transform.GetRot().z = counter * 1.0f;
		transform.SetScale(glm::vec3(0.8f, 0.8f, 0.8f));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh_normal.Draw();

		display.Update();
		counter += 0.002f;
	}

	return 0;
}
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64\glfw3.h>
#include <iostream>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Mouse.h"

int main(int argc, char* argv[])
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
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.0f,1.0f)),		// Vertices[5]
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.5f,1.0f)),		// Vertices[6]
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f,1.0f)),		// Vertices[7]
	};

	QuadCore::Display display(WIDTH, HEIGHT, "Hello World!");

	//Mesh mesh_normal(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	//Shader shader("./res/MakePlaneShader");
	Mesh mesh_obj("..\\media\\shape\\CubeHollow.obj");
	Shader shader(".\\res\\basicShader");
	Texture texture(".\\res\\bricks.jpg");
	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.001f, 1000.0f);
	Transform transform;

	Mouse mouse(display.GetWindow());
	Mouse controller(mouse, camera, transform);

	float counter = 0.0f;
	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.3f, 0.0f, 1.0f);
		
		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);
		//transform.GetPos().x += 0.001f;
		//transform.GetPos().y = cosCounter;
		transform.GetRot().x += 0.005f;
		transform.GetRot().y += 0.005f;
		transform.GetRot().z += 0.005f;
		transform.SetScale(glm::vec3(0.8f, 0.8f, 0.8f));
		//camera.SetViewProjection(glm::vec3(0.0f, 0.001f, 0.001f));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh_obj.Draw();

		display.Update();
		counter += 0.002f;
	}
	return 0;
}
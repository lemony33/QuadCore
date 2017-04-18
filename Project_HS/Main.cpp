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
#include "Controls.h"

#define LINE_NUM 100

int main(int argc, char* argv[])
{
	QuadCore::Display display(WIDTH, HEIGHT, "Hello World!");

	//unsigned int indices[] =
	//{
	//	5, 7, 6, 4
	//};

	//Vertex vertices[] =
	//{
	//	Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f,0.0f)),	// Vertices[0]
	//	Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f,0.0f)),		// Vertices[1]
	//	Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f,0.0f)),		// Vertices[2]
	//	Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(0.0f,0.0f)),		// Vertices[3]
	//	Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.0f,0.0f)),		// Vertices[4]
	//	Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.0f,1.0f)),		// Vertices[5]
	//	Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.5f,1.0f)),		// Vertices[6]
	//	Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f,1.0f)),		// Vertices[7]

	//	Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f,1.0f)),		// Vertices[8]
	//};

	//
	// Map Line
	const float width = 100.0f;
	int index = 0;
	unsigned int indices[LINE_NUM];
	Vertex vertices[100];
	for (index = 0; index < LINE_NUM; index++)
	{
		vertices[index] = { Vertex(glm::vec3((-LINE_NUM + (index*1.0f)), 0.0f, glm::pow(-1, index) * (LINE_NUM / 2.0f))) };
		indices[index] = index;
	}
		
	// Map Line
	//

#define MAP
#ifdef MAP 
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Shader shader(".\\res\\MapShader");
#endif 
#ifndef MAP
	Mesh mesh("..\\media\\shape\\CubeHollow.obj");
	Shader shader(".\\res\\objectShader");
#endif

	Texture texture(".\\res\\bricks.jpg");
	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.001f, 1000.0f);
	Transform transform;
	Controls controls(display.GetWindow());
	Controls controller(controls, camera, transform);

	while (!display.IsClosed())
	{
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		// #1_1 Vertex Shader
		// #1_2 Fragment Shader 
		shader.Bind();

		// # 2 Texture
		texture.Bind(0);

		// # 3 Map Line Color
		shader.SetLineColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

		// # 4 Transform
		shader.Update(transform, camera);

		// # 5 Draw
		mesh.Draw(GL_LINES, 0.5f);

		display.Update();
	}
	return 0;
}
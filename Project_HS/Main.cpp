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

#define LINE_VERTICAL 500
#define LINE_HORIZONTAL 500

int main(int argc, char* argv[])
{
	QuadCore::Display display(WIDTH, HEIGHT, "Hello World!");

	// Map Line
	unsigned int indices[LINE_VERTICAL + LINE_HORIZONTAL];
	Vertex vertices[LINE_VERTICAL + LINE_HORIZONTAL];
	for (int index = 0; index < LINE_VERTICAL; index++)
	{
		// Vertical
		vertices[index] =
		{ Vertex(glm::vec3((-(LINE_VERTICAL / 2) + (index*1.0f)), 0.0f, (glm::pow(-1, index) * (LINE_VERTICAL / 2.0f)))) };
		indices[index] = index;

		// Horizontal
		vertices[index + LINE_HORIZONTAL] =
		{ Vertex(glm::vec3((glm::pow(-1, index) * (LINE_HORIZONTAL / 2.0f)), 0.0f, (-(LINE_HORIZONTAL / 2) + (index*1.0f)))) };
		indices[index + LINE_HORIZONTAL] = index + LINE_HORIZONTAL;
	}

	// Map
	Mesh mesh_map(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Shader shader_map(".\\res\\MapShader");

	// Object
	Mesh mesh_object("..\\media\\shape\\CubeHollow.obj");
	Shader shader_object(".\\res\\objectShader");

	Texture texture(".\\res\\bricks.jpg");
	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.001f, 1000.0f);
	Transform transform;

	// Controller
	Controls controls(display.GetWindow());
	Controls controller(controls, camera, transform);

	while (!display.IsClosed())
	{
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		// Map
		shader_map.Bind();
		//texture.Bind(0);
		shader_map.SetLineColor(0.7f, 0.7f, 0.7f, 0.7f);
		shader_map.Update(transform, camera);
		mesh_map.Draw(GL_LINES, 2.0f, true);

		// Object
		shader_object.Bind();
		texture.Bind(0);
		//shader_object.SetLineColor(0.0f, 0.5f, 0.0f, 1.0f);
		shader_object.Update(transform, camera);
		mesh_object.Draw();

		display.Update();
	}
	return 0;
}

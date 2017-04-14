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

#define WIDTH 800
#define HEIGHT 600

//void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	if (action == GLFW_PRESS)
//	{
//		switch (key)
//		{
//		case GLFW_KEY_RIGHT:
//			printf("KEY_RIGHT\n");
//			break;
//
//		case GLFW_KEY_LEFT:
//			printf("KEY_LEFT\n");
//			break;
//
//		case GLFW_KEY_UP:
//			printf("KEY_UP\n");
//			break;
//
//		case GLFW_KEY_DOWN:
//			printf("KEY_DOWN\n");
//			break;
//
//		default:
//			printf("KEY_OTHER\n");
//			break;
//		};
//	}
//}
//void glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods)
//{
//	// Mouse-Down
//	if (action == GLFW_PRESS)
//	{
//		double x, y;
//		glfwGetCursorPos(window, &x, &y);
//		printf("MouseDown Cursor Position : [%d, %d]\n", (int)x, (int)y);
//	}
//
//	// Mouse-Up
//	if (action == GLFW_RELEASE)
//	{
//		double x, y;
//		glfwGetCursorPos(window, &x, &y);
//		printf("MouseUp Cursor Position : [%d, %d]\n", (int)x, (int)y);
//	}
//}
//void glfw_onMouseMove(GLFWwindow* window, double x, double y)
//{
//	// Mouse-Move
//	printf("MOUSE_MOVE\n");
//}
//void glfw_onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
//{
//	if ((int)yoffset == 1)
//	{
//		printf("WHEEL_UP\n");
//	}
//	if ((int)yoffset == -1)
//	{
//		printf("WHEEL_DOWN\n");
//	}
//}

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

	Mesh mesh_normal(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Shader shader("./res/MakePlaneShader");
	//Mesh mesh_obj("..\\media\\shape\\Cone.obj");
	//Shader shader(".\\res\\basicShader");
	Texture texture(".\\res\\bricks.jpg");
	Camera camera(glm::vec3(0.0f, 0.0f, -10.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.001f, 1000.0f);
	Transform transform;

	Mouse mouse(display.GetWindow());

	float counter = 0.0f;
	while (!display.IsClosed())
	{
		/*glfwSetMouseButtonCallback(display.GetWindow(), glfw_onMouseButton);
		glfwSetCursorPosCallback(display.GetWindow(), glfw_onMouseMove);
		glfwSetScrollCallback(display.GetWindow(), glfw_onMouseWheel);
		glfwSetKeyCallback(display.GetWindow(), glfw_onKey);*/

		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		
		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);
		transform.GetPos().x = sinCounter;
		transform.GetPos().y = cosCounter;
		transform.GetRot().x = counter * 2.0f;
		transform.GetRot().y = counter * 2.0f;
		transform.GetRot().z = counter * 2.0f;
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
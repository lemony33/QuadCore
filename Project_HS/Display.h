#pragma once

#include <GLEW-2.0.0_x64\GL\glew.h>
#include <GLFW-3.2.1_x64\glfw3.h>
#include <string>

class Display
{
public:
	Display() {}
	Display(int width, int height, const std::string& title);
	void Clear(float r, float g, float b, float a);
	void Update();
	bool IsClosed();
	virtual ~Display();

public:
	void GetFrameBufferSize(GLFWwindow *_window, int* width, int* height)
	{
		_window = window;
		*width = m_width;
		*height = m_height;
	}

private:
	GLFWwindow *window;
	Display(const Display& other) {}
	void operator=(const Display& other) {}

private:
	int m_width;
	int m_height;

public:
	virtual void setMouseEvent()
	{
		glfwSetMouseButtonCallback(window, onMouseButton);
		glfwSetCursorPosCallback(window, onMouseMove);
		glfwSetScrollCallback(window, onMouseWheel);
		glfwSetKeyCallback(window, onKey);
	}

	static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			switch (key)
			{
			case GLFW_KEY_RIGHT:
				printf("KEY_RIGHT\n");
				break;

			case GLFW_KEY_LEFT:
				printf("KEY_LEFT\n");
				break;

			case GLFW_KEY_UP:
				printf("KEY_UP\n");
				break;

			case GLFW_KEY_DOWN:
				printf("KEY_DOWN\n");
				break;

			default:
				printf("KEY_OTHER\n");
				break;
			};
		}
	}

	static void onMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		// Mouse-Down
		if (action == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			printf("MouseDown Cursor Position : [%d, %d]\n", (int)x, (int)y);
		}

		// Mouse-Up
		if (action == GLFW_RELEASE)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			printf("MouseUp Cursor Position : [%d, %d]\n", (int)x, (int)y);
		}
	}

	static void onMouseMove(GLFWwindow* window, double x, double y)
	{
		// Mouse-Move
		printf("MOUSE_MOVE\n");
	}

	static void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
	{
		if ((int)yoffset == 1)
			printf("WHEEL_UP\n");
		if ((int)yoffset == -1)
			printf("WHEEL_DOWN\n");
	}
};
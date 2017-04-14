#pragma once

#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64\glfw3.h>
#include <iostream>
#include "Display.h"
#include "Mouse.h"

class Mouse
{
public:
	Mouse(GLFWwindow* window)
	{
		glfwSetMouseButtonCallback(window, glfw_onMouseButton);
		glfwSetCursorPosCallback(window, glfw_onMouseMove);
		glfwSetScrollCallback(window, glfw_onMouseWheel);
		glfwSetKeyCallback(window, glfw_onKey);
	}
	virtual ~Mouse() {}

public:
	static void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
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
	static void glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			// Mouse-Down
			if (action == GLFW_PRESS)
			{
				isButtonDown = true;
				double x, y;
				glfwGetCursorPos(window, &x, &y);
				printf("Down : [ %d, %d ]\n", (int)x, (int)y);
			}

			// Mouse-Up
			if (action == GLFW_RELEASE)
			{
				isButtonDown = false;
				double x, y;
				glfwGetCursorPos(window, &x, &y);
				printf("Up : [ %d, %d ]\n", (int)x, (int)y);
			}
		}
	}
	static void glfw_onMouseMove(GLFWwindow* window, double x, double y)
	{
		// Mouse-Move
		if (isButtonDown == true)
		{
			printf("Move : [ %d , %d ]\n", (int)x, (int)y);
		}
	}
	static void glfw_onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
	{
		if ((int)yoffset == 1)
		{
			printf("WHEEL_UP\n");
		}
		if ((int)yoffset == -1)
		{
			printf("WHEEL_DOWN\n");
		}
	}

private:
	int m_xPos;
	int m_yPos;
	static bool isButtonDown;
};
bool Mouse::isButtonDown = false;
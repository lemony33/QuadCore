#pragma once

#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64\glfw3.h>
#include <iostream>
#include "Display.h"
#include "Mouse.h"

#define QUADCORE_SCROLL_UP				1
#define QUADCORE_SCROLL_DOWN		-1

class Mouse
{
public:
	Mouse(GLFWwindow* window)
	{
		glfwSetKeyCallback(window, glfw_onKey);
		glfwSetMouseButtonCallback(window, glfw_onMouseButton);
		glfwSetCursorPosCallback(window, glfw_onMouseMove);
		glfwSetScrollCallback(window, glfw_onMouseWheel);
	}
	virtual ~Mouse() {}

public:
	/* 키보드 이벤트 */
	static void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			switch (key)
			{
			case GLFW_KEY_RIGHT:
				printf("KEYBOARD RIGHT\n");
				break;

			case GLFW_KEY_LEFT:
				printf("KEYBOARD LEFT\n");
				break;

			case GLFW_KEY_UP:
				printf("KEYBOARD UP\n");
				break;

			case GLFW_KEY_DOWN:
				printf("KEYBOARD DOWN\n");
				break;

			default:
				printf("KEYBOARD TEST\n");
				break;
			};
		}
	}

	// Mouse-down
	static void glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		// Mouse Left-Down
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			// Mouse-Down
			if (action == GLFW_PRESS)
			{
				printf("Down : [ %d, %d ]\n", (int)x, (int)y);
			}
			// Mouse-Up
			if (action == GLFW_RELEASE)
			{
				printf("Up : [ %d, %d ]\n", (int)x, (int)y);
			}
		}

		// Mouse Right-Down
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			// Mouse-Down
			if (action == GLFW_PRESS)
			{

			}
			// Mouse-Up
			if (action == GLFW_RELEASE)
			{

			}
		}
	}

	// Mouse-Move
	static void glfw_onMouseMove(GLFWwindow* window, double x, double y)
	{
		// only Left-Down & Moving
		if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE))
		{
			printf("Move : [ %d , %d ]\n", (int)x, (int)y);
		}
		// only Right-Down & Moving
		else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
			&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE))
		{

		}
		// No Mouse-Down & Moving
		else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
			&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE))
		{

		}
	}

	// Mouse-Scroll
	static void glfw_onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
	{
		// Scroll-up
		if ((int)yoffset == QUADCORE_SCROLL_UP)
		{
			printf("MOUSE SCROLL  UP\n");
		}

		// Scroll-down
		if ((int)yoffset == QUADCORE_SCROLL_DOWN)
		{
			printf("MOUSE SCROLL DOWN\n");
		}
	}
};

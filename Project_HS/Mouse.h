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
		glfwSetKeyCallback(window, glfw_onKey);
		glfwSetMouseButtonCallback(window, glfw_onMouseButton);
		glfwSetCursorPosCallback(window, glfw_onMouseMove);
		glfwSetScrollCallback(window, glfw_onMouseWheel);
		glfwSetCursorEnterCallback(window, glfw_cursorEnterCallBack);

		// Set Mouse-Icon
		setMouseIcon(window);
	}
	virtual ~Mouse() 
	{
		glfwDestroyCursor(cursor);
	}

private:
	static bool isEnteredWindow;
	unsigned char pixels[16 * 16 * 4];
	GLFWcursor *cursor;

public:
	// Set Mouse-Icon
	void setMouseIcon(GLFWwindow* window)
	{
		memset(pixels, 0xff, sizeof(pixels));
		GLFWimage image;
		image.width = 16;
		image.height = 16;
		image.pixels = pixels;
		//cursor = glfwCreateCursor(&image, 0, 0);
		cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		//cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
		//cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
		//cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		//cursor = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		//cursor = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		glfwSetCursor(window, cursor);
	}

	// Key Event
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

			case GLFW_KEY_F1:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				printf("MOUSE NORMAL MODE\n");
				break;

			case GLFW_KEY_F2:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				printf("MOUSE HIDDEN MODE\n");
				break;

			case GLFW_KEY_F3:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				printf("MOUSE DISABLED MODE\n");
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

		if (isEnteredWindow == true)
		{
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
	}

	// Mouse-Move
	static void glfw_onMouseMove(GLFWwindow* window, double x, double y)
	{
		if (isEnteredWindow == true)
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
	}

	// Mouse-Scroll
	static void glfw_onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
	{
		if (isEnteredWindow == true)
		{
			// Scroll-up
			if ((int)yoffset > 0)
			{
				printf("MOUSE SCROLL  UP\n");
			}

			// Scroll-down
			if ((int)yoffset < 0)
			{
				printf("MOUSE SCROLL DOWN\n");
			}
		}
	}
	// Mouse-Hover Processing
	static void glfw_cursorEnterCallBack(GLFWwindow* window, int entered)
	{
		if (entered == GLFW_TRUE)
		{
			isEnteredWindow = true;
			printf("ENTERED WINDOW\n");
		}
		else if (entered == GLFW_FALSE)
		{
			isEnteredWindow = false;
			printf("LEFT WINDOW\n");
		}
	}
};
bool Mouse::isEnteredWindow = false;
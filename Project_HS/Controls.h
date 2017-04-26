#pragma once

#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64\glfw3.h>
#include <iostream>
#include "Display.h"
#include "Camera.h"
#include "Transform.h"
#include "Display.h"

#define GLFW_ENTERED				GLFW_TRUE
#define GLFW_LEFT						GLFW_FALSE
#define CAMERA_MOVE_UNIT	0.035f

namespace QuadCore
{
	class Controls
	{
	public:
		Controls(GLFWwindow* the_window)
		{
			window = the_window;
			glfwSetKeyCallback(window, glfw_onKey);
			glfwSetMouseButtonCallback(window, glfw_onMouseButton);
			glfwSetCursorPosCallback(window, glfw_onMouseMove);
			glfwSetScrollCallback(window, glfw_onMouseWheel);
			glfwSetCursorEnterCallback(window, glfw_cursorEnterCallBack);

			//image = imageLoader("Mouse_Icon.png");
			SetMouseCursor(window, image);
		}
		Controls(Controls& the_mouse, Camera& the_camera, Display& the_display)
		{
			mouse = &the_mouse;
			camera = &the_camera;
			display = &the_display;
		}
		virtual ~Controls() { glfwDestroyCursor(cursor); }

	private:
		GLFWwindow* window;
		GLFWcursor* cursor;
		GLFWimage image;
		static QuadCore::Camera* camera;
		static QuadCore::Controls* mouse;
		static QuadCore::Display* display;
		bool isEnteredWindow;
		int tr_x, tr_y;
		unsigned int m_TrackedID;

	public:
		virtual void onKey(int key, int action)
		{
			switch (key)
			{
			case GLFW_KEY_RIGHT:
				break;
			};
		}
		virtual void onMouseButton(int button, int action)
		{
			if (isEnteredWindow == true)
			{
				int x, y;
				GetMousePosition(x, y);
				if (button == GLFW_MOUSE_BUTTON_LEFT)
				{
					// Down
					if (action == GLFW_PRESS)
					{
						//// Read Pixels (Mouse Picking Part)
						//glReadBuffer(GL_COLOR_ATTACHMENT1);
						//glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, display->GetPixelData());
						//display->SetTrackedID
						//((display->GetPixelData()[0] << 0) 
						//	| (display->GetPixelData()[1] << 8) 
						//	| (display->GetPixelData()[2] << 16) 
						//	| (display->GetPixelData()[3] << 24));
						//std::cout << "Clicked On : " << display->GetTrackedID() << std::endl;
						display->SetCursor(x, y);
						std::cout << "Clicked On : " << display->GetTrackedID() << std::endl;
					}
					// Up
					if (action == GLFW_RELEASE)
					{

					}
				}
				if (button == GLFW_MOUSE_BUTTON_RIGHT)
				{
					// Down
					if (action == GLFW_PRESS)
					{

					}
					// Up
					if (action == GLFW_RELEASE)
					{

					}
				}
				if (button == GLFW_MOUSE_BUTTON_MIDDLE)
				{
					// Down
					if (action == GLFW_PRESS)
					{
						glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
					}
					// Up
					if (action == GLFW_RELEASE)
					{
						glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					}
				}
			}
		}
		virtual void onMouseMove(int x, int y)
		{
			if (isEnteredWindow == true)
			{
				// Left Button Down & Move
				if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE))
				{

				}
				// Right Button Down & Move
				else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE))
				{

				}

				// Wheel Button Down & Move
				else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS))
				{
					if (x > tr_x)
					{
						tr_x = x;
						camera->SetViewMove(glm::vec3(-CAMERA_MOVE_UNIT, 0.0f, 0.0f));
					}
					else if (x < tr_x)
					{
						tr_x = x;
						camera->SetViewMove(glm::vec3(CAMERA_MOVE_UNIT, 0.0f, 0.0f));
					}
					if (y > tr_y)
					{
						tr_y = y;
						camera->SetViewMove(glm::vec3(0.0f, CAMERA_MOVE_UNIT, 0.0f));
					}
					else if (y < tr_y)
					{
						tr_y = y;
						camera->SetViewMove(glm::vec3(0.0f, -CAMERA_MOVE_UNIT, 0.0f));
					}
				}

				// No Button Down & Move
				else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE))
				{

				}
			}
		}
		virtual void onMouseWheel(int wheelValue)
		{
			if (isEnteredWindow == true)
			{
				if (wheelValue > 0)
				{
					camera->SetViewMove(glm::vec3(0.0f, 0.0f, -CAMERA_MOVE_UNIT * 2));
				}
				else if (wheelValue < 0)
				{
					camera->SetViewMove(glm::vec3(0.0f, 0.0f, CAMERA_MOVE_UNIT * 2));
				}
			}
		}
		virtual void onMouseHover(int state)
		{
			if (state == GLFW_ENTERED)
			{
				isEnteredWindow = true;
			}
			else if (state == GLFW_LEFT)
			{
				isEnteredWindow = false;
			}
		}

	public:
		void SetMouseCursor(GLFWwindow* window, GLFWimage image)
		{
			cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
			glfwSetCursor(window, cursor);
		}
		void GetMousePosition(int& x, int& y)
		{
			double dx, dy;
			glfwGetCursorPos(window, &dx, &dy);
			x = static_cast<int>(floor(dx));
			y = static_cast<int>(floor(dy));
		}

	public:
		static void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			mouse->onKey(key, action);
		}
		static void glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods)
		{
			mouse->onMouseButton(button, action);
		}
		static void glfw_onMouseMove(GLFWwindow* window, double x, double y)
		{
			mouse->onMouseMove(static_cast<int>(x), static_cast<int>(y));
		}
		static void glfw_onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
		{
			mouse->onMouseWheel(static_cast<int>(yoffset));
		}
		static void glfw_cursorEnterCallBack(GLFWwindow* window, int state)
		{
			mouse->onMouseHover(state);
		}
	};
	Controls*	Controls::mouse = NULL;
	Camera* Controls::camera = NULL;
	Display* Controls::display = NULL;
}
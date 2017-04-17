#pragma once

#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64\glfw3.h>
#include <iostream>
#include "Display.h"
//#include "Controls.h"
#include "Camera.h"
#include "Transform.h"

namespace QuadCore
{
#define GLFW_ENTERED					GLFW_TRUE
#define GLFW_LEFT						GLFW_FALSE

	class Controls
	{
	public:
		Controls(GLFWwindow* window)
		{
			glfwSetKeyCallback(window, glfw_onKey);
			glfwSetMouseButtonCallback(window, glfw_onMouseButton);
			glfwSetCursorPosCallback(window, glfw_onMouseMove);
			glfwSetScrollCallback(window, glfw_onMouseWheel);
			glfwSetCursorEnterCallback(window, glfw_cursorEnterCallBack);

			//image = imageLoader("Mouse_Icon.png");
			SetMouseCursor(window, image);
		}
		Controls(Controls& the_mouse, Camera& the_camera, Transform& the_transform)
		{
			mouse = &the_mouse;
			camera = &the_camera;
			transform = &the_transform;
		}
		virtual ~Controls() { glfwDestroyCursor(cursor); }

	private:
		GLFWwindow* window;
		GLFWcursor* cursor;
		GLFWimage image;
		static QuadCore::Camera* camera;
		static QuadCore::Controls* mouse;
		static QuadCore::Transform* transform;
		bool isEnteredWindow;
		int tr_x, tr_y;
		float CAMERA_MOVE_UNIT = 0.035f;

	public:
		virtual void onKey(int key, int action)
		{
			switch (key)
			{
			case GLFW_KEY_RIGHT:
				if (action == GLFW_PRESS)
				{
					printf("Pressed Right-Key\n");
				}
				else if (action == GLFW_RELEASE)
				{
					printf("Released Right-Key\n");
				}
				break;

			case GLFW_KEY_LEFT:
				if (action == GLFW_PRESS)
				{
					printf("Pressed Left-Key\n");
				}
				else if (action == GLFW_RELEASE)
				{
					printf("Released Left-Key\n");
				}
				break;

			case GLFW_KEY_UP:
				if (action == GLFW_PRESS)
				{
					printf("Pressed Up-Key\n");
				}
				else if (action == GLFW_RELEASE)
				{
					printf("Released Up-Key\n");
				}
				break;

			case GLFW_KEY_DOWN:
				if (action == GLFW_PRESS)
				{
					printf("Pressed Down-Key\n");
				}
				else if (action == GLFW_RELEASE)
				{
					printf("Released Down-Key\n");
				}
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
			};
		}
		virtual void onMouseButton(int button, int action)
		{
			if (isEnteredWindow == true)
			{
				int x, y;
				GetMousePosition(x, y);

				// Left Button
				if (button == GLFW_MOUSE_BUTTON_LEFT)
				{
					// Down
					if (action == GLFW_PRESS)
					{
						printf("Down : [ %d, %d ]\n", (int)x, (int)y);
					}
					// Up
					if (action == GLFW_RELEASE)
					{
						printf("Up : [ %d, %d ]\n", (int)x, (int)y);
					}
				}

				// Right Button
				else if (button == GLFW_MOUSE_BUTTON_RIGHT)
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
			}
		}
		virtual void onMouseMove(int x, int y)
		{
			if (isEnteredWindow == true)
			{
				// Left Button Down & Move
				if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE))
				{
					printf("Move : [ %d , %d ]\n", (int)x, (int)y);
				}
				// Right Button Down & Move
				else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE))
				{
					if (x > tr_x)
					{
						tr_x = x;
						camera->SetViewProjection(glm::vec3(-CAMERA_MOVE_UNIT, 0.0f, 0.0f));
					}
					else if (x < tr_x)
					{
						tr_x = x;
						camera->SetViewProjection(glm::vec3(CAMERA_MOVE_UNIT, 0.0f, 0.0f));
					}
					if (y > tr_y)
					{
						tr_y = y;
						camera->SetViewProjection(glm::vec3(0.0f, CAMERA_MOVE_UNIT, 0.0f));
					}
					else if (y < tr_y)
					{
						tr_y = y;
						camera->SetViewProjection(glm::vec3(0.0f, -CAMERA_MOVE_UNIT, 0.0f));
					}
				}
				// No Button Down & Move
				else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE))
				{

				}
			}
		}
		virtual void onMouseWheel(int wheelValue)
		{
			if (isEnteredWindow == true)
			{
				// Wheel Up
				if (wheelValue > 0)
				{
					printf("MOUSE SCROLL  UP\n");
				}

				// Wheel Down
				if (wheelValue < 0)
				{
					printf("MOUSE SCROLL DOWN\n");
				}
			}
		}
		virtual void onMouseHover(int state)
		{
			// Cursor on Window
			if (state == GLFW_ENTERED)
			{
				isEnteredWindow = true;
				printf("ENTERED WINDOW\n");
			}

			// Cursor out window
			else if (state == GLFW_LEFT)
			{
				isEnteredWindow = false;
				printf("LEFT WINDOW\n");
			}
		}

	public:
		void SetMouseCursor(GLFWwindow* window, GLFWimage image)
		{
			cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
			//cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
			//cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
			//cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
			//cursor = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
			//cursor = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);

			// Set Mouse-Icon
			//cursor = glfwCreateCursor(&image, 0, 0);
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

	Controls*		QuadCore::Controls::mouse			= NULL;
	Camera*		QuadCore::Controls::camera			= NULL;
	Transform*	QuadCore::Controls::transform		= NULL;
}
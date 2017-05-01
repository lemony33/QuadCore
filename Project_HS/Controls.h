#pragma once

#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64\glfw3.h>
#include <iostream>
#include "Display.h"
#include "Camera.h"
#include "Transform.h"
#include "stb_image.h"

namespace QuadCore
{


#define GLFW_ENTERED					GLFW_TRUE
#define GLFW_LEFT						GLFW_FALSE

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

			SetMouseCursor(window);
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
		static QuadCore::Camera* camera;
		static QuadCore::Controls* mouse;
		static QuadCore::Display* display;
		bool isEnteredWindow;
		int tr_x, tr_y;
		float CAMERA_MOVE_UNIT = 0.5f;

	public:
		virtual void onKey(int key, int action)
		{
			switch (key)
			{
			case GLFW_KEY_RIGHT:
				if (action == GLFW_PRESS)
				{
				}
				else if (action == GLFW_RELEASE)
				{
				}
				break;

			case GLFW_KEY_LEFT:
				if (action == GLFW_PRESS)
				{
				}
				else if (action == GLFW_RELEASE)
				{
				}
				break;

			case GLFW_KEY_UP:
				if (action == GLFW_PRESS)
				{
				}
				else if (action == GLFW_RELEASE)
				{
				}
				break;

			case GLFW_KEY_DOWN:
				if (action == GLFW_PRESS)
				{
				}
				else if (action == GLFW_RELEASE)
				{
				}
				break;

			case GLFW_KEY_F1:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				break;

			case GLFW_KEY_F2:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				break;

			case GLFW_KEY_F3:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				break;

			case GLFW_KEY_0:
				break;
			case GLFW_KEY_1:
				break;
			case GLFW_KEY_2:
				break;
			case GLFW_KEY_3:
				break;
			case GLFW_KEY_4:
				break;
			case GLFW_KEY_5:
				break;
			case GLFW_KEY_6:
				break;
			case GLFW_KEY_7:
				break;
			case GLFW_KEY_8:
				break;
			case GLFW_KEY_9:
				break;

				// z - rotate
			case GLFW_KEY_Q:
				camera->Rotate_Axis_Z(+1.0f);
				break;
			case GLFW_KEY_E:
				camera->Rotate_Axis_Z(-1.0f);
				break;

				// x - rotate
			case GLFW_KEY_W:
				camera->Rotate_Axis_X(+1.0f);
				break;
			case GLFW_KEY_S:
				camera->Rotate_Axis_X(-1.0f);
				break;

				// y - rotate
			case GLFW_KEY_A:
				camera->Rotate_Axis_Y(+1.0f);
				break;
			case GLFW_KEY_D:
				camera->Rotate_Axis_Y(-1.0f);
				break;

			case GLFW_KEY_ESCAPE:
				glfwDestroyWindow(window);
				glfwTerminate();
				exit(EXIT_SUCCESS);
				break;
			case GLFW_KEY_SPACE:
				break;
			case GLFW_KEY_ENTER:
				if (!glfwGetWindowAttrib(window, GLFW_MAXIMIZED))
				{
					glfwMaximizeWindow(window);
				}
				else
				{
					// 스레드 문제 (키 여러번 눌림)
					//glfwSetWindowSize(window, 800, 800);
				}

				break;
			case GLFW_KEY_LEFT_SHIFT:
				glfwSetWindowSize(window, 800, 800);
				break;
			case GLFW_KEY_LEFT_CONTROL:
				break;
			case GLFW_KEY_LEFT_ALT:
				break;

			case GLFW_KEY_RIGHT_SHIFT:
				break;
			case GLFW_KEY_RIGHT_CONTROL:
				break;
			case GLFW_KEY_RIGHT_ALT:
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
					}
					// Up
					if (action == GLFW_RELEASE)
					{
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

				// Wheel Button
				else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
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
					camera->SetViewProjection(glm::vec3(tr_x - x, tr_y - y, 0.0f));
					tr_x = x;
					tr_y = y;
				}
				// Right Button Down & Move
				else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE))
				{
					camera->SetAngle(tr_x - x, -(tr_y - y));
					tr_x = x;
					tr_y = y;
				}

				// Wheel Button Down & Move
				else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS))
				{
					camera->SetViewProjection(glm::vec3(tr_x - x, tr_y - y, 0.0f));
					tr_x = x;
					tr_y = y;
				}

				// No Button Down & Move
				else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
					&& (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE))
				{
					display->SetIsMouseClicked(true);
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
					camera->MovePosition(-3.0f);
				}

				// Wheel Down
				if (wheelValue < 0)
				{
					camera->MovePosition(+3.0f);
				}
			}
		}
		virtual void onMouseHover(int state)
		{
			// Cursor on Window
			if (state == GLFW_ENTERED)
			{
				isEnteredWindow = true;
			}

			// Cursor out window
			else if (state == GLFW_LEFT)
			{
				isEnteredWindow = false;
			}
		}

	public:
		void SetMouseCursor(GLFWwindow* window)
		{
			// #1  Set Standard-Type Mouse Cursor
			cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
			//cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
			//cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
			//cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
			//cursor = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
			//cursor = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);

			// #2  Set Customed Mouse Cursor
			GLFWimage c_image;
			int numComponents;
			std::string c_fileName = "../media/cursor_greenArrow.png"; // 세로 너비 0.85cm png 이미지
			unsigned char* imageData = stbi_load((c_fileName).c_str(), &c_image.width, &c_image.height, &numComponents, 4);
			c_image.pixels = imageData;
			cursor = glfwCreateCursor(&c_image, 0, 0);
			glfwSetCursor(window, cursor);

			delete imageData;
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
	Camera*		Controls::camera = NULL;
	Display*	Controls::display = NULL;
}




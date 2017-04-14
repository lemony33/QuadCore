#pragma once

#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64\glfw3.h>
#include <iostream>
#include "Display.h"

class Mouse : public Display
{
public:
	Mouse() { setMouseEvent(); }
	virtual ~Mouse() {}

private:
	static Mouse * m;

public:
	void setMouseEvent()
	{
		printf("마우스 이벤트 세팅\n");
		//glfwSetMouseButtonCallback(window, onMouseButton);
		glfwSetCursorPosCallback(window, glfw_onMouseMove);
		//glfwSetScrollCallback(window, onMouseWheel);
		//glfwSetKeyCallback(window, onKey);
	}

	static void glfw_onMouseMove(GLFWwindow* window, double x, double y)
	{
		m->MouseMove(static_cast<int>(x), static_cast<int>(y));
	}
	virtual void MouseMove(int x, int y)
	{
		printf("Mouse Move : [ %d, %d ]", x, y);
	}
	//static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	//{

	//}
	//static void onMouseButton(GLFWwindow* window, int button, int action, int mods)
	//{

	//}
	//static void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
	//{

	//}
	//void getMousePosition(int& x, int& y)
	//{
	//	double dx, dy;
	//	glfwGetCursorPos(window, &dx, &dy);

	//	x = static_cast<int>(floor(dx));
	//	y = static_cast<int>(floor(dy));
	//}
};
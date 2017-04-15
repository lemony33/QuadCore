#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64\glfw3.h>
#include <iostream>
#include "Mouse.h"
#include "Display.h"

Mouse::Mouse()
{

}

Mouse::~Mouse()
{

}

static void glfw_onMouseMove(GLFWwindow* window, double x, double y)
{

}

void Mouse::onMouseMove()
{
	glfwSetCursorPosCallback(Display::window, glfw_onMouseMove);
}
#pragma once


#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64/glfw3.h>
#include <string>

#include <AntTweakBar.h>

/*
http://www.glfw.org/docs/latest/window_guide.html

glfwSetWindowSizeLimits(window, 200, 200, 400, 400);
glfwSetWindowSizeLimits(window, 640, 480, GLFW_DONT_CARE, GLFW_DONT_CARE);
glfwSetWindowAspectRatio(window, 16, 9);


GLFWimage images[2];
images[0] = load_icon("my_icon.png");
images[1] = load_icon("my_icon_small.png");
glfwSetWindowIcon(window, 2, images);


*/


namespace QuadCore
{


class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	void Update();
	bool IsClosed();

	virtual ~Display();

public:
	void GetWindowSize(int* width, int* height)
	{		
		*width = m_width;
		*height = m_height;
	}
	float GetWindowAspec()
	{
		return ((float)m_width / (float)m_height);
	}
	void UpdateWindowSize()
	{
		glfwGetFramebufferSize(window, &m_width, &m_height);	// ����ũ�� ������
		glViewport(0, 0, m_width, m_height);					// ����� ����
		TwWindowSize(m_width, m_height);						// TwWindow ������
	}

private:
	int m_width;
	int m_height;
	

protected:
private:
	Display(const Display& other) {}
	void operator=(const Display& other) {}

	GLFWwindow *window;

	//###
	const GLFWvidmode* mode;
	GLFWmonitor* monitor;

public:
	GLFWwindow* GetWindow()
	{
		return window;
	}
};

}
#pragma once

//#include <GL/glew.h>
#include <GLEW-2.0.0_x64/GL/glew.h>
//#include <GLFW/glfw3.h>
#include <GLFW-3.2.1_x64/glfw3.h>
#include <string>

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	void Update();
	bool IsClosed();

	virtual ~Display();

public:
	void GetFrameBufferSize(int* width, int* height) {
		*width = m_width;
		*height = m_height;
	}
private:
	int m_width;
	int m_height;
	
protected:
private:
	Display(const Display& other) {}
	void operator=(const Display& other) {}

	GLFWwindow *window;
	// gl_Context
	//bool m_isClosed;
};


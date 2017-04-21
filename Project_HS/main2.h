#pragma once

#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64\glfw3.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtx/transform.hpp>
#include <glm-0.9.8.4\glm\gtc\quaternion.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>
#include <iostream>

class Main
{
public:
	static Main& Instance();
	virtual ~Main();

public:
	int run();
	void render();
	unsigned int TrackedID() const;

protected:
	Main();

	GLFWwindow* m_window;
	friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	friend void window_size_callback(GLFWwindow* window, int width, int height);
	friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	glm::ivec2 m_Displaysize;
	glm::ivec2 m_Cursor;
	glm::vec3 m_Camera{ 0, 1, 5 };

	// FrameBuffer
	struct
	{
		glm::ivec2 size;
		unsigned int ID;
		unsigned int color0, color1, depth;
	} m_Framebuffer;

	void SetupFramebuffer();

	unsigned int m_program;
	void SetupShader();

	unsigned int m_vao, m_vbo;
	void SetupVertexArray();

	// Picking
	unsigned int m_trackedID;
};
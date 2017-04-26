#pragma once

#include <GLEW-2.0.0_x64/GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>

class RayCast
{
public:
	RayCast();
	~RayCast();

private:

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


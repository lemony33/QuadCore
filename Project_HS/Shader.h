#pragma once

#include <GLEW-2.0.0_x64\GL\glew.h>	// OpenGL Function
#include <string>		
#include "transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader(const std::string& fileName);
	void Bind();
	void Update(const Transform& transform, const Camera& camera);
	virtual ~Shader();

	// Map Line Color
	const void SetLineColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	// Map Line Color
	glm::vec4 m_lineColor;

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};


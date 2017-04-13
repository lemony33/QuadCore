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

private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};


#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GLEW-2.0.0_x64/GL/glew.h>
#include "transform.h"
#include "camera.h"


namespace QuadCore
{


class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const QuadCore::Camera& camera); // transform, camera
	const void SetLineColor(glm::vec4 color);
	virtual ~Shader();

protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}
	glm::vec4 m_lineColor;

	//transform
	enum
	{
		TRANSFORM_U,
		MODEL_U,
		VIEW_U,
		PROJECTION_U,

		LIGHT_POS_U,
		VIEW_POS_U,
		//LIGHT_COLOR_U,
		LIGHT_AMBIENT_U,
		LIGHT_DIFFUSE_U,
		LIGHT_SPECULAR_U,


		OBJECT_COLOR_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};



}

#endif
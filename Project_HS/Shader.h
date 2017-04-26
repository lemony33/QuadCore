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
		virtual ~Shader();

	private:
		Shader(const Shader& other) {}
		void operator=(const Shader& other) {}

	private:
		static const unsigned int NUM_SHADERS = 2;
		glm::vec4 m_lineColor;
		enum
		{
			TRANSFORM_U,
			NUM_UNIFORMS
		};
		GLuint m_program;
		GLuint m_shaders[NUM_SHADERS];
		GLuint m_uniforms[NUM_UNIFORMS];

	public:
		void Bind();
		void Update(const Transform& transform, const QuadCore::Camera& camera);
		const void SetLineColor(glm::vec4 color);
		glm::vec4 IntegerToColor(int i);
	};
}
#endif

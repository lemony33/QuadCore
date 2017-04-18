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
	Shader(const std::string& fileName, int MOD);
	//Shader(const std::string& fileName, const std::string& glsl);

	void Bind();
	void Update(const Transform& transform, const QuadCore::Camera& camera, const Transform& lightObjectTranform); // transform, camera

	virtual ~Shader();

protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	//transform
	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

	enum
	{
		OBJECTSHADER,

		LIGHTSHADER,

		LAMPSHADER

	};
	GLint objectColorLoc;
	GLint lightColorLoc;
	GLint lightPosLoc;
	GLint viewPosLoc;

	GLint modelLoc;
	GLint viewLoc;
	GLint projLoc;

	int ShaderMod;
};



}

#endif

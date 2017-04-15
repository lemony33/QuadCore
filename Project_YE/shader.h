#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GLEW-2.0.0_x64/GL/glew.h>
#include "transform.h"
#include "camera.h"

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const Camera& camera); // transform, camera

	virtual ~Shader();

protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	//transform
	enum
	{
		TRANSFORM_U,	// benny  GetModel()
		//POSITION_U,		//====sb7 mv_matrix			== GetModel()
		PERSPECTIVE_U,	//====sb7 proj_matrix		== m_perspective	GetViewProjection()

		NUM_UNIFORMS	// 
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif

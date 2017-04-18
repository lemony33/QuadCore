#include <GLEW-2.0.0_x64/GL/glew.h>	// OpenGL Function
#include "Shader.h"
#include <fstream>		// File Stream
#include <iostream>		// Standard
#include "Transform.h"
#include "Camera.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

/*****************************************************************************************************************************/
// CONSTRUCTOR
/*****************************************************************************************************************************/
Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader Program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader Program is invalid: ");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

/*****************************************************************************************************************************/
// DESTRUCTOR
/*****************************************************************************************************************************/
Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}

/*****************************************************************************************************************************/
// UPDATE
/*****************************************************************************************************************************/
void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetMode();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	
	// Map Line Color
	GLfloat sender[4] = { 0 };
	memcpy(&sender, &m_lineColor, sizeof(m_lineColor));
	glUniform4fv(100, 1, sender);
}

const void Shader::SetLineColor(float r, float g, float b, float a)
{
	m_lineColor = glm::vec4(r, g, b, a);
}

/*****************************************************************************************************************************/
// BIND
/*****************************************************************************************************************************/
void Shader::Bind()
{
	glUseProgram(m_program);
}

/*****************************************************************************************************************************/
// CREATE SHADER
/*****************************************************************************************************************************/
static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "[ Error ] Shader Creation Failed." << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = (GLint)text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "\n[ Error ] Shader Compliation Failed.");

	return shader;
}

/*****************************************************************************************************************************/
// LOAD SHADER_SOURCE
/*****************************************************************************************************************************/
static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "[ Error ] Unable To Load Shader : " << fileName << std::endl;
	}
	return output;
}

/*****************************************************************************************************************************/
// CHECK ERROR
/*****************************************************************************************************************************/
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
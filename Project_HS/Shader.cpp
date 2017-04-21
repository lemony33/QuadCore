#include "shader.h"
#include <iostream>
#include <fstream>

using QuadCore::Shader;


static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);


	// Vertex Shader - IN
	glBindAttribLocation(m_program, 0, "position");	// position
	glBindAttribLocation(m_program, 1, "texCoord");	// texture
	glBindAttribLocation(m_program, 2, "normal");	// lighting

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader Program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader Program is invalid: ");

	// Vertex Shader - OUT
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");

	//***
	m_uniforms[MODEL_U]			= glGetUniformLocation(m_program, "model");			// Model Matrix
	m_uniforms[VIEW_U]			= glGetUniformLocation(m_program, "view");			// View Matrix
	m_uniforms[PROJECTION_U]	= glGetUniformLocation(m_program, "projection");	// Projection Matrix

	m_uniforms[LIGHT_POS_U]		= glGetUniformLocation(m_program, "lightPos");		//
	m_uniforms[VIEW_POS_U]		= glGetUniformLocation(m_program, "viewPos");		// 
	
	//m_uniforms[LIGHT_COLOR_U]	= glGetUniformLocation(m_program, "lightColor");	// 
	m_uniforms[LIGHT_AMBIENT_U] = glGetUniformLocation(m_program, "light_ambient");	// 
	m_uniforms[LIGHT_DIFFUSE_U] = glGetUniformLocation(m_program, "light_diffuse");	// 
	m_uniforms[LIGHT_SPECULAR_U] = glGetUniformLocation(m_program, "light_specular");	// 


	m_uniforms[OBJECT_COLOR_U]	= glGetUniformLocation(m_program, "objectColor");	// 

}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(const QuadCore::Transform& transform, const QuadCore::Camera& camera) // transform, camera
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U],		1, GL_FALSE, &model[0][0]);

	glUniformMatrix4fv(m_uniforms[MODEL_U],			1, GL_FALSE, &transform.GetModel()[0][0] );			// Model
	glUniformMatrix4fv(m_uniforms[VIEW_U],			1, GL_FALSE, &camera.GetViewMatrix()[0][0]);		// View
	glUniformMatrix4fv(m_uniforms[PROJECTION_U],	1, GL_FALSE, &camera.GetProjectionMatrix()[0][0] );	// Projection

	//glUniformMatrix4fv(m_uniforms[LIGHT_POS_U],		1, GL_FALSE, &transform.GetModel()[0][0]);			// 
	//glUniformMatrix4fv(m_uniforms[VIEW_POS_U],		1, GL_FALSE, &camera.GetViewMatrix()[0][0]);		// 
	//glUniformMatrix4fv(m_uniforms[LIGHT_COLOR_U],	1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);	// 
	//glUniformMatrix4fv(m_uniforms[OBJECT_COLOR_U],	1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);	// 

	//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

	glUniform3f(m_uniforms[LIGHT_POS_U], lightPos.x, lightPos.y, lightPos.z+3.0f);
	//glUniform3f(m_uniforms[LIGHT_POS_U], lightPos.x, lightPos.y, lightPos.z); 
	glUniform3f(m_uniforms[VIEW_POS_U],		1.0f, 1.0f, 1.0f);
	
	//glUniform3f(m_uniforms[LIGHT_COLOR_U], 1.0f, 0.5f, 0.31f);
	glUniform3f(m_uniforms[LIGHT_AMBIENT_U], 1.0f, 0.0f, 0.0f);
	glUniform3f(m_uniforms[LIGHT_DIFFUSE_U], 0.3f, 0.3f, 0.8f);
	glUniform3f(m_uniforms[LIGHT_SPECULAR_U], 1.0f, 1.0f, 1.0f);

	glUniform3f(m_uniforms[OBJECT_COLOR_U],	camera.GetPos().x, camera.GetPos().y, camera.GetPos().z);
	//glUniform3f(m_uniforms[OBJECT_COLOR_U], 1.0f, 0.0f, 0.0f);

	// Draw Map 새로 추가된 부분
	GLfloat sender[4] = { 0 };
	memcpy(&sender, &m_lineColor, sizeof(m_lineColor));
	glUniform4fv(100, 1, sender);
}

// Draw Map 새로 추가된 부분
const void Shader::SetLineColor(glm::vec4 color)
{
	m_lineColor = color;
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error compiling shader type" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = (GLint)text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}

std::string LoadShader(const std::string& fileName)
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
		std::cerr << "unable to load shader: " << fileName << std::endl;
	}

	return output;
}

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
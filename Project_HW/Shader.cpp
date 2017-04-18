#include "shader.h"
#include <iostream>
#include <fstream>

using QuadCore::Shader;


static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName, int MOD)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord"); // texture
	glBindAttribLocation(m_program, 2, "normal"); // lighting

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader Program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader Program is invalid: ");

	// TRANSFORM
	if (MOD == OBJECTSHADER)
	{
		m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");

		ShaderMod = OBJECTSHADER;
	}

	else if (MOD == LIGHTSHADER)
	{
		objectColorLoc = glGetUniformLocation(m_program, "objectColor");
		lightColorLoc = glGetUniformLocation(m_program, "lightColor");
		lightPosLoc = glGetUniformLocation(m_program, "lightPos");
		viewPosLoc = glGetUniformLocation(m_program, "viewPos");
		modelLoc = glGetUniformLocation(m_program, "model");
		m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
		ShaderMod = LIGHTSHADER;
	}

	else if (MOD == LAMPSHADER)
	{
		modelLoc = glGetUniformLocation(m_program, "model");
		m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
		ShaderMod = LAMPSHADER;
	}
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

void Shader::Update(const QuadCore::Transform& transform, const QuadCore::Camera& camera, const QuadCore::Transform& lightObjectTranform) // transform, camera
{
	if (ShaderMod == OBJECTSHADER)
	{
		glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

		glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	}

	else if (ShaderMod == LIGHTSHADER)
	{
		glUniform3f(objectColorLoc, 0.5f, 0.5f, 0.31f);
		glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(lightPosLoc, transform.GetPositon().x, transform.GetPositon().y, transform.GetPositon().z);
		glUniform3f(viewPosLoc, camera.GetPos().x, camera.GetPos().y, camera.GetPos().z);

		glm::mat4 model = camera.GetViewProjection() * lightObjectTranform.GetModel();// *glm::mat4();// *transform.GetModel();

		glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
		glm::mat4 FragPosModel = glm::mat4();//transform.GetModel();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &FragPosModel[0][0]);
	}

	else if (ShaderMod == LAMPSHADER)
	{
		glm::mat4 model = glm::mat4();
				//model = glm::translate(model, transform.GetPositon());
				
				model *= camera.GetViewProjection() *transform.GetModel();;
				model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube

		glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	}

}


static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error compiling shader type" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

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
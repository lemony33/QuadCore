#include "HS_OpenGL.h"

void HS_Graphics_Simulator::init()
{
	static const char title[] = "OpenGL SuperBible - Simple Clear";
	sb7::application::init();
	memcpy(info.title, title, sizeof(title));
}

void HS_Graphics_Simulator::startup()
{
	rendering_program = compile_shaders();
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
}

GLuint HS_Graphics_Simulator::compile_shaders(void)
{
	GLuint vertex_shader;
	GLuint fragment_shader;

	static const GLchar * vertex_shader_source[] =
	{
		"#version 430 core											\n"
		"																		\n"
		"void main(void)												\n"
		"{																		\n"
		"		gl_position = vec4(0.0, 0.0, 0.5, 1.0);			\n"
		"}																		\n"
	};

	static const GLchar * fragment_shader_source[] =
	{
		"#version 430 core											\n"
		"																		\n"
		"out vec4 color;												\n"
		"																		\n"
		"void main(void)												\n"
		"{																		\n"
		"		color = vec4(0.0, 0.8, 1.0, 1.0);					\n"
		"}																		\n"
	};

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}

void HS_Graphics_Simulator::render(double currentTime)
{
	static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, red);

	glUseProgram(rendering_program);

	glDrawArrays(GL_POINTS, 0, 1);
	glPointSize(40.0f);
}

void HS_Graphics_Simulator::shutdown()
{
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vertex_array_object);
}
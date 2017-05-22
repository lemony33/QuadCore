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

	m_uniforms[LINE_COLOR_U] = glGetUniformLocation(m_program, "lineColor");	// 

}

Shader::Shader(const std::string& fileName, int shader_num, bool normal_mode)
{
	if (shader_num != 3 && shader_num != 5) {
		printf("GEROMETRY SHADER LODING FAILED \n");
		return;
	}
	printf("GEROMETRY SHADER LODING...!!!\n");


	std::string shader_filepath = "../resources/shaders/Final/";

	/// 1. Vertex Shader
	std::string vertexfn = "Vertex_1_default";
	vertexfn = shader_filepath + vertexfn;

	/// 2. Tessellation Control Shader
	std::string tessllcs = "Tessellation_1_Control";
	tessllcs = shader_filepath + tessllcs;

	/// 3. Tessellation Evaluation Shader
	std::string tesslles = "Tessellation_1_Evaluation";
	tesslles = shader_filepath + tesslles;

	/// 4. Geometry Shader
	std::string geometry = "Geometry_1_default";
	if (normal_mode)
		geometry = "Geometry_2_normal_view";
	geometry = shader_filepath + geometry;

	/// 5. Fragment Shader
	// fileName : 5_1_Phong / 5_2 Multi-Phong / 5_3 Multi-Phong-Rim


	m_program = glCreateProgram();

	if (shader_num == 5)
	{
	}
	m_shaders[0] = CreateShader(LoadShader(vertexfn + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(tessllcs + ".tcs"), GL_TESS_CONTROL_SHADER);
	m_shaders[2] = CreateShader(LoadShader(tesslles + ".tes"), GL_TESS_EVALUATION_SHADER);
	m_shaders[3] = CreateShader(LoadShader(geometry + ".gs"), GL_GEOMETRY_SHADER);
	m_shaders[4] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);



	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);


	// Vertex Shader - IN
	glBindAttribLocation(m_program, 0, "position");	// position
	glBindAttribLocation(m_program, 1, "texCoord");	// texture
	glBindAttribLocation(m_program, 2, "normal");	// lighting

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader Program linking failed: ");
	printf((fileName+"\n").c_str());

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader Program is invalid: ");

	// Vertex Shader - OUT
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");

	//***
	m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");			// Model Matrix
	m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "view");			// View Matrix
	m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "projection");	// Projection Matrix

	m_uniforms[LIGHT_POS_U] = glGetUniformLocation(m_program, "lightPos");		//
	m_uniforms[VIEW_POS_U] = glGetUniformLocation(m_program, "viewPos");		// 

																				//m_uniforms[LIGHT_COLOR_U]	= glGetUniformLocation(m_program, "lightColor");	// 
	m_uniforms[LIGHT_AMBIENT_U] = glGetUniformLocation(m_program, "light_ambient");	// 
	m_uniforms[LIGHT_DIFFUSE_U] = glGetUniformLocation(m_program, "light_diffuse");	// 
	m_uniforms[LIGHT_SPECULAR_U] = glGetUniformLocation(m_program, "light_specular");	// 
	m_uniforms[OBJECT_COLOR_U] = glGetUniformLocation(m_program, "objectColor");	// 

	m_uniforms[LINE_COLOR_U] = glGetUniformLocation(m_program, "lineColor");	// 

	m_uniforms[EXPLODE_FACTOR] = glGetUniformLocation(m_program, "explode_factor");	// 
	m_uniforms[NORMAL_VIEWER] = glGetUniformLocation (m_program, "i_normal_viewer");
	m_uniforms[NORMAL_LENGTH] = glGetUniformLocation(m_program, "normal_length");

	m_uniforms[TESS_LEVEL_INNER] = glGetUniformLocation(m_program, "tess_level_inner");
	m_uniforms[TESS_LEVEL_OUTER] = glGetUniformLocation(m_program, "tess_level_outer"); 
	m_uniforms[TESS_LEVEL_SCALE] = glGetUniformLocation(m_program, "tess_level_scale");
	
	m_uniforms[NORMAL_MODE] = glGetUniformLocation(m_program, "i_normal_mode");
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

void Shader::Update(const QuadCore::Transform& transform, const QuadCore::Camera& camera, SHADER_NAME fs_mode) // transform, camera
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U],		1, GL_FALSE, &model[0][0]);

	glUniformMatrix4fv(m_uniforms[MODEL_U],			1, GL_FALSE, &transform.GetModel()[0][0] );			// Model
	glUniformMatrix4fv(m_uniforms[VIEW_U],			1, GL_FALSE, &camera.GetViewMatrix()[0][0]);		// View
	glUniformMatrix4fv(m_uniforms[PROJECTION_U],	1, GL_FALSE, &camera.GetProjectionMatrix()[0][0] );	// Projection

	glUniform3f(glGetUniformLocation(m_program, "pos"),
		transform.GetPos_const().x, transform.GetPos_const().y, transform.GetPos_const().z);

	// for 2D UI Shader
	glm::mat4 guiMVP = glm::mat4(1.0f) * transform.GetModel();
	glUniformMatrix4fv(100, 1, GL_FALSE, &guiMVP[0][0]);

	///
	glUniform1f(m_uniforms[TESS_LEVEL_INNER], m_tess_level_inner);
	glUniform1f(m_uniforms[TESS_LEVEL_OUTER], m_tess_level_outer);
	glUniform1f(m_uniforms[TESS_LEVEL_SCALE], m_tess_level_scale);

	glUniform1i(m_uniforms[NORMAL_MODE], m_i_normal_mode);


	///
	//glUniform1f(m_uniforms[EXPLODE_FACTOR], sinf((float)timer.GetCounter_timer() * 8.0f) * cosf((float)timer.GetCounter_timer() * 6.0f) * 0.7f + 0.1f);
	glUniform1f(m_uniforms[EXPLODE_FACTOR], m_explode_factor);

	glUniform1i(m_uniforms[NORMAL_VIEWER], m_normal_viewer);
	glUniform1f(m_uniforms[NORMAL_LENGTH], m_normal_length);

	///m_normal_viewer

	switch (fs_mode)
	{
	case SHADER_NAME::Phong_Shading:
		SetUniform_Fragment_phong(camera.GetPos());
		break;
	case SHADER_NAME::Line_Shading:
		SetUniform__Fragment_gridmap();
		break;
	}
}

// Draw Map 새로 추가된 부분
const void Shader::SetLineColor(glm::vec4 color)
{
	m_lineColor = color;
	SetUniform__Fragment_gridmap();
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




inline void Shader::SetUniform_Fragment_phong(glm::vec3 cameraposition)
{
	////glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
	//glm::vec3 lightPos(-0.2f, -1.0f, -0.3f);

	glUniform3f(m_uniforms[LIGHT_POS_U], lightPos.x, lightPos.y, lightPos.z);

	glUniform3f(m_uniforms[VIEW_POS_U], cameraposition.x, cameraposition.y, cameraposition.z);


	glUniform3f(m_uniforms[LIGHT_AMBIENT_U], 0.1f, 0.1f, 0.1f);
	glUniform3f(m_uniforms[LIGHT_DIFFUSE_U], 0.4f, 0.4f, 0.4f);
	glUniform3f(m_uniforms[LIGHT_SPECULAR_U], 0.5f, 0.5f, 0.5f);

	glUniform3f(m_uniforms[OBJECT_COLOR_U], 1.0f, 0.0f, 0.0f);


	for (int i = 0; i < 5; i++)
	{
		glUniform3f(glGetUniformLocation(m_program, pointLight[i].uniformName[0].c_str()),
			pointLight[i].positiion.x, pointLight[i].positiion.y, pointLight[i].positiion.z);

		glUniform3f(glGetUniformLocation(m_program, pointLight[i].uniformName[1].c_str()),
			pointLight[i].ambient.x, pointLight[i].ambient.y, pointLight[i].ambient.z);

		glUniform3f(glGetUniformLocation(m_program, pointLight[i].uniformName[2].c_str()),
			pointLight[i].diffuse.x, pointLight[i].diffuse.y, pointLight[i].diffuse.z);

		glUniform3f(glGetUniformLocation(m_program, pointLight[i].uniformName[3].c_str()),
			pointLight[i].specular.x, pointLight[i].specular.y, pointLight[i].specular.z);

		glUniform1f(glGetUniformLocation(m_program, pointLight[i].uniformName[4].c_str()),
			pointLight[i].constant);
		glUniform1f(glGetUniformLocation(m_program, pointLight[i].uniformName[5].c_str()),
			pointLight[i].linear);
		glUniform1f(glGetUniformLocation(m_program, pointLight[i].uniformName[6].c_str()),
			pointLight[i].quadratic);
		//std::cout << pointLight[i].uniformName[6].c_str() << " " << pointLight[i].quadratic << std::endl;
	}
}
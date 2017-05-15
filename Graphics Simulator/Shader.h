#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GLEW-2.0.0_x64/GL/glew.h>
#include "transform.h"
#include "camera.h"

#include "enum_type.h"


namespace QuadCore
{

	class PointLight
	{
	public:
		int index;
		std::string uniformName[7];
		glm::vec3 positiion;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float constant;
		float linear;
		float quadratic;

		PointLight(int num = 0,
			glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3& amb = glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3& diff = glm::vec3(0.8f, 0.8f, 0.8f),
			glm::vec3& spec = glm::vec3(1.0f, 1.0f, 1.0f),
			float con = 1.0f,
			float lin = 0.09f,
			float qua = 0.032f)
		{
			index = num;
			positiion = pos;
			ambient = amb;
			diffuse = diff;
			specular = spec;
			constant = con;
			linear = lin;
			quadratic = qua;
		}

		void SetValue(int num,
			glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3& amb = glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3& diff = glm::vec3(0.8f, 0.8f, 0.8f),
			glm::vec3& spec = glm::vec3(1.0f, 1.0f, 1.0f),
			float con = 1.0f,
			float lin = 0.09f,
			float qua = 0.032f)
		{
			index = num;

			if (check)
			{
				for (int i = 0; i < 7; i++)
				{
					char number = index + 48;
					{
						uniformName[i] = "pointLights[";
						uniformName[i] += number;
						uniformName[i].append(uniforms[i]);
					}
				}
			}

			check = false;
			positiion = pos;
			ambient = amb;
			diffuse = diff;
			specular = spec;
			constant = con;
			linear = lin;
			quadratic = qua;
		}
	private:
		bool check = true;
		std::string uniforms[7] = { "].lightPos", "].light_ambient", "].light_diffuse", "].light_specular", "].constant", "].linear", "].quadratic" };
	};



class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const QuadCore::Camera& camera, SHADER_NAME fs_mode = SHADER_NAME::Phong_Shading); // transform, camera
	void Update_UI(const Transform& transform, const QuadCore::Camera& camera, SHADER_NAME fs_mode = SHADER_NAME::Phong_Shading); // transform, camera
	const void SetLineColor(glm::vec4 color);
	virtual ~Shader();

protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}
	glm::vec4 m_lineColor;


	// 내부적으로만 호출되는 쉐이더 전용 함수들
	// 함수명 규칙: inline void SetUniform_쉐이더종류_이름()
private:
	inline void SetUniform_Fragment_phong(glm::vec3 cameraposition)
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
	inline void SetUniform__Fragment_gridmap()
	{
		glUniform4fv(m_uniforms[LINE_COLOR_U], 1, &m_lineColor[0]);
	}

	// Shader Layout #
private:
	//transform
	enum
	{
		// VS - Phone, Line
		TRANSFORM_U,		// 사용안함
		MODEL_U,
		VIEW_U,
		PROJECTION_U,

		// FS - lamp
		LIGHT_POS_U,
		VIEW_POS_U,

		// FS - Phone Shading
		LIGHT_AMBIENT_U,
		LIGHT_DIFFUSE_U,
		LIGHT_SPECULAR_U,
		OBJECT_COLOR_U,		//  사용안함

		// FS - Line Shading
		LINE_COLOR_U,


		NUM_UNIFORMS
	};

	GLuint m_program;					// Program
	GLuint m_shaders[NUM_SHADERS];		// Shader
	GLuint m_uniforms[NUM_UNIFORMS];	// Uniform

	///
	PointLight pointLight[5];

public:
	void InputpointLight(Transform* lightPositions, glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular)
	{
		for (int i = 0; i < 5; i++)
		{
			pointLight[i].SetValue(i, lightPositions[i].GetPos(), ambient[i], diffuse[i], specular[i]);
		}
	}

};



}

#endif

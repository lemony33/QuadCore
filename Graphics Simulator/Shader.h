#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GLEW-2.0.0_x64/GL/glew.h>
#include "transform.h"
#include "camera.h"

#include "enum_type.h"


#include "Timer.h"

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
	Shader::Shader(const std::string& fileName, int shader_num, bool normal_mode = false);

	void Bind();
	void Update(const Transform& transform, const QuadCore::Camera& camera, SHADER_NAME fs_mode = SHADER_NAME::Phong_Shading); // transform, camera
	const void SetLineColor(glm::vec4 color);
	virtual ~Shader();

protected:
private:
	static const unsigned int NUM_SHADERS = 3;
	//static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}
	glm::vec4 m_lineColor;

	Timer timer;


	
public:
	//inline void SetUniform_explode_factor(float currentCount);
	// 내부적으로만 호출되는 쉐이더 전용 함수들
	// 함수명 규칙: inline void SetUniform_쉐이더종류_이름()
private:
	inline void SetUniform_Fragment_phong(glm::vec3 cameraposition);
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

		// EFFECT for Geometry Shader
		EXPLODE_FACTOR,
		EXPLODE_SPEED,
		NORMAL_VIEWER,
		NORMAL_LENGTH,

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

	inline void Shader::SetUniform_explode_factor(float currentCount, bool mode = true)
	{
		if (!mode){
			m_explode_factor = 0.0f;
			return;
		}
		//glUniform1f(explode_factor_location, sinf((float)currentTime * 8.0f) * cosf((float)currentTime * 6.0f) * 0.7f + 0.1f);
		//m_explode_factor = sinf(currentCount * 8.0f / 100.0f) * cosf(currentCount * 6.0f / 100.0f) * 3.0f + 0.1f;
		m_explode_factor = sinf(currentCount * 8.0f / 100.0f * m_explode_speed) * cosf(currentCount * 6.0f / 100.0f * m_explode_speed) * m_explode_factor_scale;
		if (m_explode_factor < 0.0f)
			m_explode_factor = 0.0f;
	}

	inline void Set_NormalViewer(bool flag)
	{
		m_normal_viewer = flag;
	}
	inline void Set_NormalLength(float length)
	{
		m_normal_length = length;
	}
	inline void Set_ExplodeSpeed(float length)
	{
		m_explode_speed = length;
	}
	inline void Set_ExplodeFactor(float factor)
	{
		m_explode_factor_scale = factor;
	}

private:
	bool m_normal_viewer = false;
	float m_normal_length;
	float m_explode_factor;
	float m_explode_speed;

	float m_explode_factor_scale;
};



}

#endif

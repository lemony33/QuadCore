#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GLEW-2.0.0_x64/GL/glew.h>
#include "transform.h"
#include "camera.h"

#include "enum_type.h"


namespace QuadCore
{


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
		//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

		glUniform3f(m_uniforms[LIGHT_POS_U], lightPos.x, lightPos.y, lightPos.z);
		//glUniform3f(m_uniforms[LIGHT_	POS_U], lightPos.x, lightPos.y, lightPos.z); 
		//glUniform3f(m_uniforms[VIEW_POS_U], 1.0f, 1.0f, 1.0f);
		glUniform3f(m_uniforms[VIEW_POS_U], cameraposition.x, cameraposition.y, cameraposition.z);

		//glUniform3f(m_uniforms[LIGHT_COLOR_U], 1.0f, 0.5f, 0.31f);
		glUniform3f(m_uniforms[LIGHT_AMBIENT_U], 1.0f, 1.0f, 1.0f);
		glUniform3f(m_uniforms[LIGHT_DIFFUSE_U], 0.5f, 0.5f, 0.5f);
		glUniform3f(m_uniforms[LIGHT_SPECULAR_U], 1.0f, 1.0f, 1.0f);

		//glUniform3f(m_uniforms[OBJECT_COLOR_U], camera.GetPos().x, camera.GetPos().y, camera.GetPos().z);
		glUniform3f(m_uniforms[OBJECT_COLOR_U], 1.0f, 0.0f, 0.0f);
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

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};



}

#endif

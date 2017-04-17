#pragma once

#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtx\transform.hpp>

#define WIDTH 800
#define HEIGHT 600

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_position = pos;
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
		m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	virtual ~Camera() {}

private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;

public:
	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	//(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.001f, 1000.0f);
	void SetViewProjection(glm::vec3 position/*, glm::mat4 perspective, glm::vec3 forward, glm::vec3 up*/)
	{
		//m_perspective = perspective;
		m_position += position;
		//m_forward = forward;
		//m_up = up;
	}
};


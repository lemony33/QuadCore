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

	void SetViewMove(glm::vec3 position)
	{
		m_position += position;
	}
	void SetViewRotation(float angle)
	{
		m_perspective += angle;
	}
};


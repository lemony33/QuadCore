#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED


#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtx/transform.hpp>


namespace QuadCore
{


class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(0, 0, -1);
		m_up = glm::vec3(0, 1, 0);
	}

	void Update(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(0, 0, -1);
		m_up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

protected:
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;


	// Controls.h ���� ���
public:
	void SetViewMove(glm::vec3 position)
	{
		m_position += position;
	}
	void SetViewRotation(float angle)
	{
		m_perspective += angle;
	}
};


}

#endif
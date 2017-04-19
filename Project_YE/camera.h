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
		//m_forward = glm::vec3(0, 0, -1);
		m_up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}
	
	inline glm::mat4 GetViewMatrix() const
	{
		//glm::translate(x, y, z);
		//printf("%f,%f,%f\n", m_position.x, m_position.y, m_position.z);
		return glm::lookAt(m_position, m_position + m_forward, m_up);//glm::translate(m_position);
	}

	inline glm::mat4 GetProjectionMatrix() const
	{
		//glm::perspective(fov,paspect, zNear, zFar)
		return m_perspective;
	}

	inline glm::vec3 GetPos() const
	{
		return m_position;
	}

protected:
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;

	float ForwardAngle = 0;
	float UpAngle = 0;
	float sensitivity = 0.005;

	// Controls.h ���� ���
public:

	//(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.001f, 1000.0f);
	void SetViewProjection(glm::vec3 position/*, glm::mat4 perspective, glm::vec3 forward, glm::vec3 up*/)
	{
		//m_perspective = perspective;
		m_position += position;
		//m_forward = forward;
		//m_up = up;
	}

	void MovePosition(float depth)
	{		
		//m_position.z += depth;
		if (depth > 0)
			m_position -= m_forward;
		else if (depth < 0)
			m_position += m_forward;
	}

	void SetAngle(float fangle, float uangle)
	{
		ForwardAngle += fangle * sensitivity;
		UpAngle += uangle * sensitivity;
		m_forward = glm::vec3(-1.0f * sinf(ForwardAngle) * cosf(UpAngle),
							-1.0f * sinf(UpAngle),
							-1.0f * cosf(ForwardAngle) * cosf(UpAngle));
		printf("Forward ( %.2f, %.2f, %.2f)\n", m_forward.x, m_forward.y, m_forward.z);
	}
};


}

#endif
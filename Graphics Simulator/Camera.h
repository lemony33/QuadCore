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
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	inline glm::mat4 GetViewMatrix() const
	{
		return glm::lookAt(m_position, m_position + m_forward, m_up);
		//return glm::lookAt(m_position, glm::vec3() + m_forward, m_up);
	}

	inline glm::mat4 GetProjectionMatrix() const
	{
		//glm::perspective(fov,paspect, zNear, zFar)
		return m_perspective;
	}

	inline glm::vec3 GetPos() const
	{
		//printf(" ( %.2f,%.2f , %.2f ) \n", m_position.x, m_position.y, m_position.z);
		return m_position;
	}

	inline glm::vec3 GetForward() const
	{
		return m_forward;
	}

	inline glm::vec3 GetUpward() const
	{
		return m_up;
	}

	inline glm::vec3 GetSide() const
	{
		return glm::cross(m_forward, m_up);
	}

protected:
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;

	glm::mat4 m_orthographic;

	float sensitivity = 0.1f;

	glm::mat4 m_ortho;

	// Controls.h ���� ���
public:

	void SetViewProjection(glm::vec3 position)
	{
		if (position.x > 0.0f)
			m_position -= glm::cross(m_forward, m_up) * sensitivity;
		else if (position.x < 0.0f)
			m_position += glm::cross(m_forward, m_up) * sensitivity;

		if (position.y > 0.0f)
			m_position += m_up * sensitivity;						
		else if (position.y < 0.0f)
			m_position -= m_up * sensitivity;						
	}

	/*
		[ ���콺 �ٷ� �� ��&�ƿ� ]
		����ȭ��� : ������ġ(m_position)
		���������� : �պ���(m_foward) �������� �̵�
	*/
	void MovePosition(float depth)
	{
		if (depth > 0)
			m_position -= m_forward;
		else if (depth < 0)
			m_position += m_forward;
	}


	/*
		[ ���콺�� ȸ�� - XY�� ���� ]
		����ȭ��� : �պ���(m_foward), ������(m_up)
		���������� : z�� ȸ���� �Ͼ�� �ʵ��� �������ٰ�
	*/
	void SetAngle(float fangle, float uangle)
	{
		fangle *= sensitivity * 5;
		uangle *= sensitivity * 5;

		// x�� ���� ȸ��
		glm::vec3 side = glm::cross(m_forward, m_up);
		glm::vec3 x_forward = Rotate_Axis_normal(side, -uangle, m_forward);
		glm::vec3 x_up = Rotate_Axis_normal(side, -uangle, m_up);


		// y�� ���� ȸ��
		glm::vec3 y_forward = Rotate_Axis_normal(x_up, fangle, x_forward);

		m_forward = x_forward;
		m_up = x_up;

		m_forward = y_forward;
		m_up = glm::vec3(0, 1, 0);	// ���� ���Ǽ��� ���� ī�޶� ������ ���� �����ش�.

		// ���� ������ ���� ���� �Է�
		degree_Axis_Y += fangle;
		if (degree_Axis_Y >= 360.0f)
			degree_Axis_Y -= 360.0f;

		degree_Axis_X += -uangle;
		if (degree_Axis_X >= 360.0f)
			degree_Axis_X -= 360.0f;

		////// ���� �����ɶ� �����߻�
		//float mid  = glm::dot(glm::vec3(0,m_up.y, m_up.z), glm::vec3(0, 1, 0))/2;
		//if (uangle > 0)
		//	degree_Axis_X += -mid;
		//else
		//	degree_Axis_X += +mid;
		////degree_Axis_X += -uangle/2;
		//if (degree_Axis_X >= 360.0f)
		//	degree_Axis_X -= 360.0f;

		////// ���� �����ɶ� �����߻�
		////degree_Axis_X += -uangle;
		////if (degree_Axis_X >= 360.0f)
		////	degree_Axis_X -= 360.0f;

		////// Z�൵ ���� �ʿ�
		//////degree_Axis_Z += degree_s2s;
		////degree_Axis_Z += degree_Axis_Z;
		////if (degree_Axis_Z >= 360.0f)
		////	degree_Axis_Z -= 360.0f;
	}

	/**********************************************************************************

		[ Quaternion Rotate : ������� ȸ�� ]
		  - normal vector(a,b,c)�� ������ �� p(x,y,z)�� �袪��ŭ ȸ���Ѵ�.

		q = { sin(��/2)n, cos(��/2) }

		R_q(p) = qpq'��
			   = cos��P + (1-cos��)(N��P)N + sin��(N��P)

		�� => inner product or dot product
		�� => outer product or cross product

	**********************************************************************************/
	inline glm::vec3 Rotate_Axis_normal(glm::vec3 normal, float degree, glm::vec3 point)
	{
		float radians = degree * glm::pi<float>() / 180.0f;

		float q = cosf(radians) + sinf(radians);

		glm::vec3 mov_pos = (cosf(radians) * point)
			+ ((1 - cosf(radians)) * glm::dot(normal, point) * normal)
			+ (sinf(radians) * glm::cross(normal, point));
		return mov_pos;
	}


	/*
		[ Z�� ���� ȸ�� ]
		����ȭ��� : ������(m_up)
		���������� : ī�޶� z���� ���������� ���ϱ� ������ ������ �ݴ�� ����ؾ��Ѵ�.
	*/
	void Rotate_Axis_Z(float angle)
	{
		degree_Axis_Z += angle;

		if (degree_Axis_Z >= 360.0f)
			degree_Axis_Z -= 360.0f;

		m_up = Rotate_Axis_normal(m_forward, -angle, m_up);

		/*	error
			���� ���������ϴ� �ܼ�ȸ��, �ٸ� ���� ������ ����Ұ�
		***********************************************************/
		//degree_Axis_Z += angle;

		//if (degree_Axis_Z >= 360.0f)
		//	degree_Axis_Z -= 360.0f;

		//float radians = degree_Axis_Z * glm::pi<float>() / 180.0f;

		//m_up.x = -sinf(radians);
		//m_up.y = +cosf(radians);
		//**********************************************************

		///printf("[Axis_Z] - degree: %.2f, radians: %.2f ),\t", degree_Axis_Z, radians);
		//printf("FORWARD( %.2f, %.2f, %.2f ),\t", m_forward.x, m_forward.y, m_forward.z);
		//printf("UP( %.2f, %.2f, %.2f ),\t", m_up.x, m_up.y, m_up.z);
		//printf("\n");
	}

	float degree_Axis_X = 0.0f;
	float degree_Axis_Y = 0.0f;
	float degree_Axis_Z = 0.0f;

	glm::vec3 GetRot()
	{
		float rad = glm::pi<float>() / 180.0f;
		return glm::vec3(degree_Axis_X*rad, degree_Axis_Y*rad, degree_Axis_Z*rad);
	}

	/*
		[ Y�� ���� ȸ�� ]
		����ȭ��� : �պ���(m_foward)
		���������� : X
	*/
	void Rotate_Axis_Y(float angle)
	{
		degree_Axis_Y += angle;

		if (degree_Axis_Y >= 360.0f)
			degree_Axis_Y -= 360.0f;

		m_forward = Rotate_Axis_normal(m_up, angle, m_forward);

		/*	error
			���� ���������ϴ� �ܼ�ȸ��, �ٸ� ���� ������ ����Ұ�
		***********************************************************/
		//degree_Axis_Y += angle;

		//if (degree_Axis_Y >= 360.0f)
		//	degree_Axis_Y -= 360.0f;

		//float radians = degree_Axis_Y * glm::pi<float>() / 180.0f;

		//m_forward.x = -sinf(radians);
		//m_forward.z = -cosf(radians);
		//**********************************************************


		///printf("[Axis_Y] - degree: %.2f, radians: %.2f ),\t", degree_Axis_Y, radians);
		//printf("FORWARD( %.2f, %.2f, %.2f ),\t", m_forward.x, m_forward.y, m_forward.z);
		//printf("UP( %.2f, %.2f, %.2f ),\t", m_up.x, m_up.y, m_up.z);
		//printf("\n");
	}

	/*
		[ X�� ���� ȸ�� ]
		����ȭ��� : �պ���(m_foward), ������(m_up)
		���������� : 90�� ������ ������ �� �ֵ��� ���ÿ� ��ȭ���Ѿ� �Ѵ�.
	*/
	void Rotate_Axis_X(float angle)
	{
		degree_Axis_X += angle;

		if (degree_Axis_X >= 360.0f)
			degree_Axis_X -= 360.0f;

		glm::vec3 side = glm::cross(m_forward, m_up);
		m_forward = Rotate_Axis_normal(side, angle, m_forward);
		m_up = Rotate_Axis_normal(side, angle, m_up);


		/*	error
			���� ���������ϴ� �ܼ�ȸ��, �ٸ� ���� ������ ����Ұ�
		***********************************************************/
		//degree_Axis_X += angle;

		//if (degree_Axis_X >= 360.0f)
		//	degree_Axis_X -= 360.0f;

		//float radians = degree_Axis_X * glm::pi<float>() / 180.0f;

		//m_forward.y = +sinf(radians);
		//m_forward.z = -cosf(radians);

		//m_up.y = +cosf(radians);
		//m_up.z = +sinf(radians);
		//**********************************************************

		///printf("[Axis_X] - degree: %.2f, radians: %.2f ),\t", degree_Axis_X, radians);
		//printf("FORWARD( %.2f, %.2f, %.2f ),\t", m_forward.x, m_forward.y, m_forward.z);
		//printf("UP( %.2f, %.2f, %.2f ),\t", m_up.x, m_up.y, m_up.z);
		//printf("\n");
	}
};

}


#endif
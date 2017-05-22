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

	// Controls.h 에서 사용
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
		[ 마우스 휠로 줌 인&아웃 ]
		＠변화요소 : 현재위치(m_position)
		※주의할점 : 앞벡터(m_foward) 방향으로 이동
	*/
	void MovePosition(float depth)
	{
		if (depth > 0)
			m_position -= m_forward;
		else if (depth < 0)
			m_position += m_forward;
	}


	/*
		[ 마우스로 회전 - XY축 기준 ]
		＠변화요소 : 앞벡터(m_foward), 위벡터(m_up)
		※주의할점 : z축 회전이 일어나지 않도록 보정해줄것
	*/
	void SetAngle(float fangle, float uangle)
	{
		fangle *= sensitivity * 5;
		uangle *= sensitivity * 5;

		// x축 기준 회전
		glm::vec3 side = glm::cross(m_forward, m_up);
		glm::vec3 x_forward = Rotate_Axis_normal(side, -uangle, m_forward);
		glm::vec3 x_up = Rotate_Axis_normal(side, -uangle, m_up);


		// y축 기준 회전
		glm::vec3 y_forward = Rotate_Axis_normal(x_up, fangle, x_forward);

		m_forward = x_forward;
		m_up = x_up;

		m_forward = y_forward;
		m_up = glm::vec3(0, 1, 0);	// 조작 편의성을 위해 카메라 방향을 위로 맞춰준다.

		// 각도 보정을 위한 정보 입력
		degree_Axis_Y += fangle;
		if (degree_Axis_Y >= 360.0f)
			degree_Axis_Y -= 360.0f;

		degree_Axis_X += -uangle;
		if (degree_Axis_X >= 360.0f)
			degree_Axis_X -= 360.0f;

		////// 축이 누적될때 오류발생
		//float mid  = glm::dot(glm::vec3(0,m_up.y, m_up.z), glm::vec3(0, 1, 0))/2;
		//if (uangle > 0)
		//	degree_Axis_X += -mid;
		//else
		//	degree_Axis_X += +mid;
		////degree_Axis_X += -uangle/2;
		//if (degree_Axis_X >= 360.0f)
		//	degree_Axis_X -= 360.0f;

		////// 축이 누적될때 오류발생
		////degree_Axis_X += -uangle;
		////if (degree_Axis_X >= 360.0f)
		////	degree_Axis_X -= 360.0f;

		////// Z축도 보정 필요
		//////degree_Axis_Z += degree_s2s;
		////degree_Axis_Z += degree_Axis_Z;
		////if (degree_Axis_Z >= 360.0f)
		////	degree_Axis_Z -= 360.0f;
	}

	/**********************************************************************************

		[ Quaternion Rotate : 사원수의 회전 ]
		  - normal vector(a,b,c)를 축으로 점 p(x,y,z)를 θ˚만큼 회전한다.

		q = { sin(θ/2)n, cos(θ/2) }

		R_q(p) = qpq'¹
			   = cosθP + (1-cosθ)(N·P)N + sinθ(N×P)

		· => inner product or dot product
		× => outer product or cross product

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
		[ Z축 기준 회전 ]
		＠변화요소 : 위벡터(m_up)
		※주의할점 : 카메라가 z축의 역방향으로 향하기 때문에 각도를 반대로 계산해야한다.
	*/
	void Rotate_Axis_Z(float angle)
	{
		degree_Axis_Z += angle;

		if (degree_Axis_Z >= 360.0f)
			degree_Axis_Z -= 360.0f;

		m_up = Rotate_Axis_normal(m_forward, -angle, m_up);

		/*	error
			축을 기준으로하는 단순회전, 다른 축의 움직임 적용불가
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
		[ Y축 기준 회전 ]
		＠변화요소 : 앞벡터(m_foward)
		※주의할점 : X
	*/
	void Rotate_Axis_Y(float angle)
	{
		degree_Axis_Y += angle;

		if (degree_Axis_Y >= 360.0f)
			degree_Axis_Y -= 360.0f;

		m_forward = Rotate_Axis_normal(m_up, angle, m_forward);

		/*	error
			축을 기준으로하는 단순회전, 다른 축의 움직임 적용불가
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
		[ X축 기준 회전 ]
		＠변화요소 : 앞벡터(m_foward), 위벡터(m_up)
		※주의할점 : 90도 각도를 유지할 수 있도록 동시에 변화시켜야 한다.
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
			축을 기준으로하는 단순회전, 다른 축의 움직임 적용불가
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
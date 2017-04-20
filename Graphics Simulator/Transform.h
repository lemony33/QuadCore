#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtx/transform.hpp>

namespace QuadCore
{

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale) {}

	void Init (const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		m_pos = pos;
		m_rot = rot;
		m_scale = scale;
	}

	// 4x4 matrix
	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMatrix = glm::translate(m_pos);
		glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(m_scale);

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix; // 순서 중요!
	}

	inline glm::vec3& GetPos() { return m_pos; }
	inline glm::vec3& GetRot() { return m_rot; }
	inline glm::vec3& GetScale() { return m_scale; }

	inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
	inline void SetRot(const glm::vec3& rot) { m_rot = rot; }
	inline void SetScale(const glm::vec3& scale) { m_scale = scale; }

protected:
private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};


}

#endif
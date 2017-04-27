/*
	���������� �����ϴ� �⺻ �ڷ���
*/
#pragma once


#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Transform.h"
#include "Coordinates.h"

#include <string>


namespace QuadCore
{

class iShape
{
public:
	iShape() : shape_path("../media/shape/")
	{}
	virtual ~iShape()
	{
		delete(m_transform);
		delete(m_mesh);
		delete(m_shader);
		delete(m_texture);
		delete(m_coordinate);
	}
	
public:
	// ���: ��ü�� ��ȯ���� �Է��Ѵ�.
	// �Է�: ��ġ, ����, ũ��
	virtual void transform(glm::vec3 position, glm::vec3 rotation = glm::vec3(), glm::vec3 scale = glm::vec3(1, 1, 1))
	{
		m_transform->SetPos(position);
		m_transform->SetRot(rotation);
		m_transform->SetScale(scale);
	}

	// ���: ��ü�� �׷��ش�
	virtual void Draw(QuadCore::Camera* camera, bool enable_coor = false) = 0;

	virtual QuadCore::Transform* GetTransform()
	{
		return m_transform;
	}

	// ���: ��ü�� ��ġ�� �����Ѵ�
	virtual void position(glm::vec3 position)
	{
		m_transform->SetPos(position);
	}

	// ���: ��ü�� �̵���Ų��
	virtual void translate(glm::vec3 position)
	{
		m_transform->SetPos(m_transform->GetPos() + position);
		//m_transform->SetPos(position);
	}
		
	// ���: ��ü�� ȸ����Ų��
	virtual void rotate(glm::vec3 rotation)
	{
		m_transform->SetRot(rotation);
		//m_transform->SetRot(m_transform->GetRot() + rotation);
	}

	// ���: ��ü�� ũ�⸦ ��ȭ��Ų��
	virtual void scale(glm::vec3 scale)
	{
		m_transform->SetScale(scale);
	}

	virtual Shader* GetShader()
	{
		return m_shader;
	}

protected:
	std::string m_shape_name = "iShape";

	QuadCore::Transform*	m_transform;
	QuadCore::Mesh*			m_mesh;

	QuadCore::Shader*		m_shader;
	QuadCore::Texture*		m_texture;

	Coordinates* m_coordinate;

	//int m_shader;
	//int m_texture;

	//Collider collider;
	//Physics* physics;

	std::string shape_path;
};

}




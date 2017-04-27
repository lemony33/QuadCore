/*
	도형정보를 정의하는 기본 자료형
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
	// 기능: 물체의 변환값을 입력한다.
	// 입력: 위치, 각도, 크기
	virtual void transform(glm::vec3 position, glm::vec3 rotation = glm::vec3(), glm::vec3 scale = glm::vec3(1, 1, 1))
	{
		m_transform->SetPos(position);
		m_transform->SetRot(rotation);
		m_transform->SetScale(scale);
	}

	// 기능: 물체를 그려준다
	virtual void Draw(QuadCore::Camera* camera, bool enable_coor = false) = 0;

	virtual QuadCore::Transform* GetTransform()
	{
		return m_transform;
	}

	// 기능: 물체의 위치를 설정한다
	virtual void position(glm::vec3 position)
	{
		m_transform->SetPos(position);
	}

	// 기능: 물체를 이동시킨다
	virtual void translate(glm::vec3 position)
	{
		m_transform->SetPos(m_transform->GetPos() + position);
		//m_transform->SetPos(position);
	}
		
	// 기능: 물체를 회전시킨다
	virtual void rotate(glm::vec3 rotation)
	{
		m_transform->SetRot(rotation);
		//m_transform->SetRot(m_transform->GetRot() + rotation);
	}

	// 기능: 물체의 크기를 변화시킨다
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




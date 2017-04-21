/*
	도형정보를 정의하는 기본 자료형
*/
#pragma once


#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Transform.h"

#include <string>


namespace QuadCore
{

class Shape
{
public:
	Shape() : shape_path("../media/shape/")
	{}
	virtual ~Shape() {}
	
	virtual void Draw(const QuadCore::Camera* camera, glm::vec3 pos = glm::vec3()) = 0;

protected:

	QuadCore::Transform*	m_transform;
	QuadCore::Mesh*			m_mesh;

	QuadCore::Shader*		m_shader;
	QuadCore::Texture*		m_texture;

	//int m_shader;
	//int m_texture;

	//Collider collider;
	//Physics* physics;

	//QuadCore::Shader*		m_shader;
	//QuadCore::Texture*		m_texture;	

	std::string shape_path;
};

}
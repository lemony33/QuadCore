/*
���������� �����ϴ� �⺻ �ڷ���
*/
#pragma once


#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Transform.h"


namespace QuadCore
{

	class Shape
	{
	public:
		Shape();
		virtual ~Shape();

	protected:

		virtual void Draw() = 0;

		QuadCore::Transform*	transform;
		QuadCore::Mesh*			m_mesh;

		int m_shader;
		int m_texture;

		//Collider collider;
		//Physics* physics;

		//QuadCore::Shader*		m_shader;
		//QuadCore::Texture*		m_texture;	
	};

}
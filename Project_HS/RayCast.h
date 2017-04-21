#pragma once

#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64/glfw3.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtx/transform.hpp>
#include <iostream>

#include "Controls.h"
//#include "Transform.h"
//#include "Shader.h"
//#include "Mesh.h"

namespace QuadCore
{
	class RayCast
	{
	public:
		RayCast() {}
		//RayCast(Controls& the_controls);
		virtual ~RayCast();

	private:
		//Controls* QuadCore::RayCast::m_Controls;
		//Transform* QuadCore::RayCast::m_Transform;
		//Shader* QuadCore::RayCast::m_Shader;
		//Vertex* QuadCore::RayCast::m_Vertex;
		//Mesh* QuadCore::RayCast::m_Mesh;

		int m_RayX;
		int m_RayY;
		int m_RayZ;

	public:
		// #1  ���� ���콺�� ��ġ�� �κп��� RayCasting �ϴ� ��ǥ �� ��ȯ
		void GetRayValue();

		// #2  ������Ʈ�� RayCast ��ǥ�� �浹�ϴ��� ���� ��ȯ
		void IsCollidedWithObject();

		// #3  ���õ� ���� ���� ��ȯ
		void ChangeColor();
	};
}
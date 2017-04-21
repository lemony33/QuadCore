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
		// #1  현재 마우스가 위치한 부분에서 RayCasting 하는 좌표 값 반환
		void GetRayValue();

		// #2  오브젝트와 RayCast 좌표가 충돌하는지 여부 반환
		void IsCollidedWithObject();

		// #3  선택된 도형 색상 변환
		void ChangeColor();
	};
}
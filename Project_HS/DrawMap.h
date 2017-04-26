#pragma once

#include <GLEW-2.0.0_x64/GL/glew.h>
#include <GLFW-3.2.1_x64\glfw3.h>
#include <iostream>
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

typedef unsigned int UINT;

namespace QuadCore
{
	class DrawMap
	{
	public:
		DrawMap();
		DrawMap(Camera& the_camera);
		virtual ~DrawMap();

	private:
		Transform m_Transform;
		Camera* m_Camera;

	private:
		UINT* m_Indices;
		Vertex* m_Vertices;
		Mesh* m_Mesh;
		Shader* m_Shader;
		int*** m_PositionArray;
		int m_MatrixSize;

	public:
		void SetProperty(int matrixSize, float thickness, glm::vec4 color);
		void DrawPlane();

		// Plane Position-Array
		void SetPosition(glm::vec3 pos, int value = 1);
		int GetPosition(glm::vec3 pos);
		void PrintArray();
		//
	};
}
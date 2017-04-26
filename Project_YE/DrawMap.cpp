#include "DrawMap.h"

QuadCore::DrawMap::DrawMap()
{

}

QuadCore::DrawMap::DrawMap(Camera& the_camera)
{
	m_Camera = &the_camera;

	Transform the_transform;
	m_Transform = the_transform;
}

QuadCore::DrawMap::~DrawMap()
{
	delete[] m_Indices;
	delete[] m_Vertices;
}

void QuadCore::DrawMap::SetProperty(int matrixSize, float thickness, glm::vec4 color)
{
	// Matrix(Mesh)
	m_Indices = new UINT[(matrixSize * 4)]();
	m_Vertices = new Vertex[(matrixSize * 4)]();
	for (int index = 0; index < (matrixSize * 2); index++)
	{
		// Vertical
		m_Vertices[index] =
		{ Vertex(glm::vec3((-(matrixSize / 2) + ((index / 2) * 1.0f) + 0.5f), 0.0f, (glm::pow(-1, index) * (matrixSize / 2.0f))), glm::vec2(0.0f, 0.0f)) };
		m_Indices[index] = index;

		// Horizontal
		m_Vertices[index + matrixSize * 2] =
		{ Vertex(glm::vec3((glm::pow(-1, index) * (matrixSize / 2.0f)), 0.0f, (-((matrixSize / 2)) + ((index / 2) * 1.0f)) + 0.5f), glm::vec2(0.0f, 0.0f)) };
		m_Indices[index + (matrixSize * 2)] = index + (matrixSize * 2);
	}
	m_Mesh = new Mesh(m_Vertices, matrixSize * 4, m_Indices, matrixSize * 4);

	// Shader
	m_Shader = new Shader("../media/MapShader");

	// Line Color
	m_Shader->SetLineColor(color);

	// Line Thickness(Width)
	glLineWidth(thickness);
}

void QuadCore::DrawMap::DrawPlane()
{
	m_Shader->Bind();
	m_Shader->Update(m_Transform, *m_Camera, Line_Shading);
	m_Mesh->DrawLines();
}
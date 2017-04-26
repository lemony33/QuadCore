#include "DrawMap.h"

#define HEIGHT_ARRAY_SIZE 2

QuadCore::DrawMap::DrawMap()
{

}

QuadCore::DrawMap::DrawMap(Camera& the_camera)
{
	m_Camera = &the_camera;

	Transform the_transform;
	m_Transform = the_transform;

	// Allocate Position-Array
	m_PositionArray = new int **[100](); // X-Array
	for (int x = 0; x < 100; x++)
	{
		m_PositionArray[x] = new int *[200]();
		for (int y = 0; y < 200; y++)
		{
			m_PositionArray[x][y] = new int[300]();
		}
	}
}

QuadCore::DrawMap::~DrawMap()
{
	delete[] m_Indices;
	delete[] m_Vertices;
	delete[] m_PositionArray;
}

void QuadCore::DrawMap::SetProperty(int matrixSize, float thickness, glm::vec4 color)
{
	// Set matrixSize
	m_MatrixSize = matrixSize;

	// Matrix(Mesh)
	m_Indices = new UINT[(matrixSize * 4)]();
	m_Vertices = new Vertex[(matrixSize * 4)]();
	for (int index = 0; index < (matrixSize * 2); index++)
	{
		// Vertical
		m_Vertices[index] =
		{ Vertex(glm::vec3((-(matrixSize / 2) + ((index / 2) * 1.0f) + 0.5f), -0.5f, (glm::pow(-1, index) * (matrixSize / 2.0f))), glm::vec2(0.0f, 0.0f)) };
		m_Indices[index] = index;

		// Horizontal
		m_Vertices[index + matrixSize * 2] =
		{ Vertex(glm::vec3((glm::pow(-1, index) * (matrixSize / 2.0f)), -0.5f, (-((matrixSize / 2)) + ((index / 2) * 1.0f)) + 0.5f), glm::vec2(0.0f, 0.0f)) };
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
	m_Shader->Update(m_Transform, *m_Camera);
	m_Mesh->DrawLines();
}

// Set Plane Position-Array
void QuadCore::DrawMap::SetPosition(glm::vec3 pos, int value)
{
	((int)pos.x > ((m_MatrixSize - 2) / 2)) ? (pos.x = (float)m_MatrixSize) : pos.x = pos.x;
	((int)pos.z > ((m_MatrixSize - 2) / 2)) ? (pos.z = (float)m_MatrixSize) : (pos.z = pos.z);
	((int)pos.y > (HEIGHT_ARRAY_SIZE - 1)) ? (pos.y = (float)(HEIGHT_ARRAY_SIZE - 1)) : (pos.y = pos.y);

	m_PositionArray[(int)pos.x + ((m_MatrixSize - 2) / 2)][(int)pos.y][(int)pos.z + ((m_MatrixSize - 2) / 2)] = value;
}

// Get Plane Position-Array
int QuadCore::DrawMap::GetPosition(glm::vec3 pos)
{
	return m_PositionArray[(int)pos.x][(int)pos.y][(int)pos.z];
}

// Print Plane Position-Array
void QuadCore::DrawMap::PrintArray()
{
	std::cout << std::endl;
	for (int y = 0; y < HEIGHT_ARRAY_SIZE; y++)
	{
		std::cout << " [ Y = " << y << " ]" << std::endl;

		for (int z = 0; z < m_MatrixSize - 1; z++)
		{
			for (int x = 0; x < m_MatrixSize - 1; x++)
			{
				std::cout << m_PositionArray[x][y][z] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

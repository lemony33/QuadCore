#include "Mesh.h"
#include <vector>
#include <string>
#include "obj_loader.h"

/*****************************************************************************************************************************/
// CONSTRUCTOR
/*****************************************************************************************************************************/
Mesh::Mesh(const std::string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}
	InitMesh(model);
}

/*****************************************************************************************************************************/
// DESTRUCTOR
/*****************************************************************************************************************************/
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

/*****************************************************************************************************************************/
// INIT MESH
/*****************************************************************************************************************************/
void Mesh::InitMesh(const IndexedModel& model)
{
	m_drawCount = model.indices.size();

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

/*****************************************************************************************************************************/
// DRAW
/*****************************************************************************************************************************/
void Mesh::Draw(int mode, float thickness)
{
	glBindVertexArray(m_vertexArrayObject);

	glLineWidth(thickness);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// # 라인 부드럽게
	//glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	// # 점선
	//glEnable(GL_LINE_STIPPLE);
	//glLineStipple(4, 0xAAAA);

	// # 드로우
	glDrawElements(mode, m_drawCount, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
}

// 참고 사이트
// GL_LINES 와 GL_LINES_STRIP 차이점 외 ... http://geofhagopian.net/sablog/Sabblog-7-5-05.htm
// glEnable(GL_LINE_STIPPLE) , glLineStipple(4, pattern) ... 선 그리기 사이트 https://skyfe79.gitbooks.io/opengl-tutorial/content/chapter4.html

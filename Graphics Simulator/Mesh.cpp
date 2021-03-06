#include "mesh.h"
#include "obj_loader.h"
#include <vector>

using QuadCore::Mesh;


// 
Mesh::Mesh(const std::string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);
}


// 
Mesh::Mesh(QuadCore::Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	InitMesh(model);	
}


// 
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}


// 
void Mesh::InitMesh(const QuadCore::IndexedModel& model)
{
	m_drawCount = model.indices.size(); // obj file

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	// position
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// texture / texCoord
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Lighting
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// obj file
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}


// 
void Mesh::Draw(bool poly_mode, bool tessellation_mode)
{
	// 기본설정 값 3이므로 실행할 필요없음
	//glPatchParameteri(GL_PATCH_VERTICES, 3);	// for tessellation 
	if (poly_mode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// for tessellation
		//glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FLAT);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glBindVertexArray(m_vertexArrayObject);
	
	if (!tessellation_mode)
	{
		glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0); // obj file
	}
	else
	{
		glDrawElements(GL_PATCHES, m_drawCount, GL_UNSIGNED_INT, 0); // for tessellation (tri)
		//glDrawArrays(GL_PATCHES, 0, 4); // for tessellation (quad)
	}	

	glBindVertexArray(0);
}


// 선을 width 굵기로 그린다.
void Mesh::DrawLines(GLfloat width)
{
	glBindVertexArray(m_vertexArrayObject);

	glLineWidth(width);

	// Draw Map
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glDrawElements(GL_LINES, m_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDisable(GL_POLYGON_SMOOTH);
}
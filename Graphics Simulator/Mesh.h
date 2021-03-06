#ifndef MESH_H
#define MESH_H

#include <glm-0.9.8.4/glm/glm.hpp>
#include <GLEW-2.0.0_x64/GL/glew.h>
#include "obj_loader.h"

namespace QuadCore
{

class Vertex
{
public:
	Vertex() {} // Draw Map 새로 추가된 부분
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0))
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}
	inline glm::vec3* GetPos() { return &pos; }				// position
	inline glm::vec2* GetTexCoord() { return &texCoord; }	// texture
	inline glm::vec3* GetNormal() { return &normal; }		// lighting

protected:
private:
	glm::vec3 pos;		// position
	glm::vec2 texCoord;	// texture
	glm::vec3 normal;	// lighting
};


class Mesh
{
public:
	//Mesh(Vertex* vertices, unsigned int numVertices); // 원본
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices); // obj file
	Mesh(const std::string& fileName);

	void Draw(bool poly_mode = false, bool tessellation_mode = false);
	void DrawLines(GLfloat width = 1.0f);

	virtual ~Mesh();

protected:
private:
	Mesh(const Mesh& other) {}
	void operator=(const Mesh& other) {}

	void InitMesh(const IndexedModel& model);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB, // texture
		NORMAL_VB, // lighting

		INDEX_VB, // obj file

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

	//int MOD;
	//enum {
	//	OBJFILE,
	//	VERTICES
	//};
};

}

#endif
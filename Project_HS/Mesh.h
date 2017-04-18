#pragma once


#include <GLEW-2.0.0_x64\GL\glew.h>		// OpenGL Function
#include <glm-0.9.8.4\glm\glm.hpp>	// OpenGL Math
#include "obj_loader.h"

class Vertex
{
public:
	Vertex() {}
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord = glm::vec2(0.0f, 0.0f), const glm::vec3& normal = glm::vec3(0.0f, 0.0f, 0.0f))
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}
	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	void Draw(int mode = GL_TRIANGLES, float thickness = 1.0f, bool polygon = false);
	virtual ~Mesh();

private:
	Mesh(const Mesh& other) {}
	void operator=(const Mesh& other) {}
	void InitMesh(const IndexedModel& model);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};


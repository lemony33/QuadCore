#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

using QuadCore::Vertex;
using QuadCore::Mesh;
using QuadCore::Shader;


class Coordinates
{
public:
	Coordinates(float line_length = 1.0f) { Init(line_length); }
	virtual ~Coordinates()	{}

	void Init(QuadCore::Transform* transform, QuadCore::Camera* camera, float line_length = 1.0f);
	void Init_UI(QuadCore::Transform* transform, QuadCore::Camera* camera, float line_length = 1.0f);
	
	void Init(float line_length = 1.0f);
	void Init_Link(QuadCore::Transform* transform, QuadCore::Camera* camera);

	void Draw(GLfloat width = 2.0f);

private:
	QuadCore::Transform* m_transform;
	QuadCore::Camera* m_camera;

	Mesh* axis_x;
	Mesh* axis_y;
	Mesh* axis_z;

	Shader* coor_shader;
};


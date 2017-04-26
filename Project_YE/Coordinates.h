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
	Coordinates() {}
	void Init(QuadCore::Transform* transform, QuadCore::Camera* camera, float line_length = 1.0f)
	{


		Vertex vertex_0 = Vertex(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(), glm::vec3());
		Vertex vertex_x = Vertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(), glm::vec3());
		Vertex vertex_y = Vertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(), glm::vec3());
		Vertex vertex_z = Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(), glm::vec3());

		vertex_x.GetPos()->x *= line_length;
		vertex_y.GetPos()->y *= line_length;
		vertex_z.GetPos()->z *= line_length;

		unsigned int indices[] = { 0, 1, };
		Vertex vertices_x[] = { vertex_0, vertex_x };
		Vertex vertices_y[] = { vertex_0, vertex_y };
		Vertex vertices_z[] = { vertex_0, vertex_z };

		axis_x = new Mesh(vertices_x, sizeof(vertices_x) / sizeof(vertices_x[0]), indices, sizeof(indices) / sizeof(indices[0]));
		axis_y = new Mesh(vertices_y, sizeof(vertices_y) / sizeof(vertices_x[0]), indices, sizeof(indices) / sizeof(indices[0]));
		axis_z = new Mesh(vertices_z, sizeof(vertices_z) / sizeof(vertices_x[0]), indices, sizeof(indices) / sizeof(indices[0]));

		coor_shader = new Shader("../media/MapShader");


		m_transform = transform;
		m_camera = camera;

	}

	virtual ~Coordinates()
	{
	}

	void Draw(GLfloat width = 2.0f)
	{
		coor_shader->Bind();
		coor_shader->Update(*m_transform, *m_camera);

		coor_shader->SetLineColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));	axis_x->DrawLines(width);
		coor_shader->SetLineColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));	axis_y->DrawLines(width);
		coor_shader->SetLineColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));	axis_z->DrawLines(width);
	}

private:
	QuadCore::Transform* m_transform;
	QuadCore::Camera* m_camera;

	Mesh* axis_x;
	Mesh* axis_y;
	Mesh* axis_z;

	Shader* coor_shader;
};


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
	void Init(QuadCore::Transform* transform, QuadCore::Camera* camera)
	{
		Vertex vertex_0 = Vertex(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(), glm::vec3());
		Vertex vertex_x = Vertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(), glm::vec3());
		Vertex vertex_y = Vertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(), glm::vec3());
		Vertex vertex_z = Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(), glm::vec3());

		vertex_x.GetPos()->x *= coordinate_length;
		vertex_y.GetPos()->y *= coordinate_length;
		vertex_z.GetPos()->z *= coordinate_length;

		unsigned int indices[] = { 0, 1, };
		Vertex vertices_x[] = { vertex_0, vertex_x };
		Vertex vertices_y[] = { vertex_0, vertex_y };
		Vertex vertices_z[] = { vertex_0, vertex_z };

		coordinate_x = new Mesh(vertices_x, sizeof(vertices_x) / sizeof(vertices_x[0]), indices, sizeof(indices) / sizeof(indices[0]));
		coordinate_y = new Mesh(vertices_y, sizeof(vertices_y) / sizeof(vertices_x[0]), indices, sizeof(indices) / sizeof(indices[0]));
		coordinate_z = new Mesh(vertices_z, sizeof(vertices_z) / sizeof(vertices_x[0]), indices, sizeof(indices) / sizeof(indices[0]));

		coor_shader = new Shader("../media/MapShader");


		m_transform = transform;
		m_camera = camera;

	}

	virtual ~Coordinates()
	{
	}

	void Draw()
	{
		coor_shader->Bind();
		coor_shader->Update(*m_transform, *m_camera);

		coor_shader->SetLineColor(glm::vec4(1.0, 0.0, 0.0, 1.0));	coordinate_x->DrawLines(3.0f);
		coor_shader->SetLineColor(glm::vec4(0.0, 1.0, 0.0, 1.0));	coordinate_y->DrawLines(3.0f);
		coor_shader->SetLineColor(glm::vec4(0.0, 0.0, 1.0, 1.0));	coordinate_z->DrawLines(3.0f);
	}

private:
	QuadCore::Transform* m_transform;
	QuadCore::Camera* m_camera;

	Mesh* coordinate_x;
	Mesh* coordinate_y;
	Mesh* coordinate_z;

	Shader* coor_shader;

	const float coordinate_length = 3.0f;
};


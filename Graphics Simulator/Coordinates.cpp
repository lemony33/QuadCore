#include "Coordinates.h"


// 좌표축을 line_length 길이로 그려준다.
// Transform, Camera 객체를 연결시켜 준다.
void Coordinates::Init(QuadCore::Transform* transform, QuadCore::Camera* camera, float line_length)
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

	coor_shader = new Shader("../resources/shaders/Final/MapShader");
	
	m_transform = transform;
	m_camera = camera;
}


// 좌표축을 line_length 길이로 그려준다.
void Coordinates::Init(float line_length)
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

	coor_shader = new Shader("../resources/shaders/Final/MapShader");
}


// 좌표축을 line_length 길이로 그려준다.
// Transform, Camera 객체를 연결시켜 준다.
void Coordinates::Init_UI(QuadCore::Transform* transform, QuadCore::Camera* camera, float line_length)
{
	Vertex vertex_0 = Vertex(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(), glm::vec3());
	Vertex vertex_x = Vertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(), glm::vec3());
	Vertex vertex_y = Vertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(), glm::vec3());
	Vertex vertex_z = Vertex(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(), glm::vec3());

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

	coor_shader = new Shader("../resources/shaders/Final/MapShader_2D_HUD");


	m_transform = transform;
	m_camera = camera;

}


// Transform, Camera 객체를 연결시켜 준다.
void Coordinates::Init_Link(QuadCore::Transform* transform, QuadCore::Camera* camera)
{
	m_transform = transform;
	m_camera = camera;
}


// 좌표축을 width 굵기로 그려준다.
void Coordinates::Draw(GLfloat width)
{
	coor_shader->Bind();
	coor_shader->Update(*m_transform, *m_camera);

	coor_shader->SetLineColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));	axis_x->DrawLines(width);
	coor_shader->SetLineColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));	axis_y->DrawLines(width);
	coor_shader->SetLineColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));	axis_z->DrawLines(width);
}
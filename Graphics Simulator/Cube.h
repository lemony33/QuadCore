#pragma once

#include "Shape.h"


namespace QuadCore
{

class Cube : public Shape
{
public:

	Cube()
	{
		Init();
	}

	virtual ~Cube()
	{
	}

	void Init()
	{
		m_transform = new Transform;
		std::string filename = shape_path + "Cube.obj";
		m_mesh = new Mesh(filename);

		//Shader shader1("../media/new_shader/basicShader_light");
		m_shader = new Shader("../media/new_shader/basicShader_light");
		m_texture = new Texture("../media/res/bricks.jpg");

		//QuadCore::Transform*	m_transform;
		//QuadCore::Mesh*			m_mesh;
	}

	virtual void Draw(const QuadCore::Camera* camera, glm::vec3 pos = glm::vec3())
	{
		m_shader->Bind();
		m_texture->Bind(0);

		m_transform->SetPos(pos);

		m_shader->Update(*m_transform, *camera);
		m_mesh->Draw();
	}

	/*
	shader1.Bind();
		texture1.Bind(0);

		float r = 3.0f;
		transform3.SetPos(glm::vec3(-r / 2.0f, 0, 0));
		transform3.GetPos().x += sinf(counter) * r;
		transform3.GetPos().y += cosf(counter) * r;

		transform3.GetRot().y = counter * 0.9f;
		transform3.GetRot().x = counter * 0.7f;

		//transform3.GetPos().z += tanf(counter) * r;
		shader1.Update(transform3, camera);
		mesh3.Draw();
		coor_model_3.Draw();
	*/

};

}
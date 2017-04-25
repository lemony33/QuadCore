#pragma once

#include "iShape.h"


namespace QuadCore
{

class Cube : public iShape
{
public:

	Cube(glm::vec3 position)
	{
		m_shape_name = "Cube";

		m_transform = new Transform(position);
		std::string filename = shape_path + m_shape_name + ".obj";
		m_mesh = new Mesh(filename);

		//Shader shader1("../media/new_shader/basicShader_light");
		m_shader = new Shader("../media/new_shader/basicShader_light");
		m_texture = new Texture("../media/res/bricks.jpg");

		m_coordinate = new Coordinates(1.0f);
	}

	virtual ~Cube()
	{
		delete(m_transform);
		delete(m_mesh);
		delete(m_shader);
		delete(m_texture);
		delete(m_coordinate);
	}

	virtual void transform(glm::vec3 position, glm::vec3 rotation = glm::vec3(), glm::vec3 scale = glm::vec3(1,1,1))
	{
		m_transform->SetPos(position);
		m_transform->SetRot(rotation);
		m_transform->SetScale(scale);
	}
		
	virtual void Draw(QuadCore::Camera* camera)
	{
		m_shader->Bind();
		m_texture->Bind(0);

		m_shader->Update(*m_transform, *camera);
		m_mesh->Draw();

		m_coordinate->Init_Link(m_transform, camera);
		m_coordinate->Draw(10.0f);
	}
	
};

}
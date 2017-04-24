#pragma once

//#include "Texture.h"
#include "Shape.h"
#include <vector>

#include "Cube.h"


namespace QuadCore
{

class ShapeManager
{
public:
	ShapeManager()
	{
		Insert_Object(glm::vec3(1, 1, 0));
		Insert_Object(glm::vec3(2, 2, 0));
		Insert_Object(glm::vec3(3, 3, 0));
		Insert_Object(glm::vec3(4, 4, 0));
		Insert_Object(glm::vec3(5, 5, 0));
		Insert_Object(glm::vec3(1, 5, 3));

	}
	virtual ~ShapeManager();


	void Insert_Object(glm::vec3 pos)
	{
		//m_shape = new Cube;
		//Cube* cube = new Cube;
		//cube->transform(pos);
		m_shape_list.push_back(new Cube(pos));

		//m_shape_list.at(0)->transform(pos);
	}


	void Delete_Objet()
	{
	}

	
	
	void DrawAll()
	{
		////cube.Draw(camera);
		////m_shape->Draw(camera);
		////m_shape_list.at(0)->Draw(camera, glm::vec3(0,1,0));


		float delim = 0.7;

		////m_shape_list.at(0)->transform(glm::vec3(delim * m_sinCounter, delim * m_cosCounter, 1));
		//Transform* transform = m_shape_list.at(0)->GetTransform();

		//transform->SetPos(glm::vec3(0, 0, 0));
		//transform->SetPos(glm::vec3(1.1, 1.1, 0));

		//transform->GetPos().y += delim * m_sinCounter;
		//transform->GetPos().x += delim * m_cosCounter;
		//transform->GetRot().y = m_sinCounter * 0.5f;
		//transform->GetRot().x = m_cosCounter * 0.3f;

		for (int i = 0; i < m_shape_list.size(); i++)
		{
			m_shape_list.at(i)->Draw(m_camera);
			m_shape_list.at(i)->rotate(glm::vec3(m_cosCounter * 0.3f, m_sinCounter * 0.5f, 0));
		}
	}
	
	void SetCounter(float sinCounter, float cosCounter)
	{
		m_sinCounter = sinCounter;
		m_cosCounter = cosCounter;
	}
	
	void Init(Camera* camera)
	{
		m_camera = camera;
	}

private:
	//QuadCore::Texture m_texture;
	//Cube cube;
	//Shape* m_shape;
	std::vector<Shape*> m_shape_list;

	QuadCore::Camera* m_camera;

	typename glm::vec3 vec;

	float m_sinCounter;
	float m_cosCounter;
};

}

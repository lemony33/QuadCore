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
		Insert_Object();
	}
	virtual ~ShapeManager();


	void Insert_Object()
	{
		//m_shape = new Cube;
		m_shape_list.push_back(new Cube);


		vec = { 1, 1, 0 };
		m_shape_list.at(0)->transform(vec);
	}


	void Delete_Objet()
	{
	}

	
	
	void Run(QuadCore::Camera* camera)
	{
		//cube.Draw(camera);
		//m_shape->Draw(camera);
		//m_shape_list.at(0)->Draw(camera, glm::vec3(0,1,0));


		float delim = 0.7;

		

		//m_shape_list.at(0)->transform(glm::vec3(delim * m_sinCounter, delim * m_cosCounter, 1));
		Transform* transform = m_shape_list.at(0)->GetTransform();

		transform->SetPos(glm::vec3(0, 0, 0));
		transform->SetPos(glm::vec3(1.1, 1.1, 0));

		transform->GetPos().y += delim * m_sinCounter;
		transform->GetPos().x += delim * m_cosCounter;
		transform->GetRot().y = m_sinCounter * 0.5f;
		transform->GetRot().x = m_cosCounter * 0.3f;

		m_shape_list.at(0)->Draw(camera);
	}
	
	void SetCounter(float sinCounter, float cosCounter)
	{
		m_sinCounter = sinCounter;
		m_cosCounter = cosCounter;
	}

private:
	//QuadCore::Texture m_texture;
	//Cube cube;
	//Shape* m_shape;
	std::vector<Shape*> m_shape_list;

	typename glm::vec3 vec;

	float m_sinCounter;
	float m_cosCounter;
};

}

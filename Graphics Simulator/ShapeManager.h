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
		//m_shape = new Cube;
		m_shape_list.push_back(new Cube);
	}
	virtual ~ShapeManager();


	void Run(const QuadCore::Camera* camera)
	{
		//cube.Draw(camera);
		//m_shape->Draw(camera);
		//m_shape_list.at(0)->Draw(camera, glm::vec3(0,1,0));

		vec = { 1, 1, 0 };
		m_shape_list.at(0)->Draw(camera, vec);
	}
	

private:
	//QuadCore::Texture m_texture;
	//Cube cube;
	//Shape* m_shape;
	std::vector<Shape*> m_shape_list;

	typename glm::vec3 vec;
};

}

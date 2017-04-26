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


	// 물체를 리스트에 추가한다
	void Insert_Object(glm::vec3 pos /*= glm::vec3()*/)
	{
		//m_shape = new Cube;
		//Cube* cube = new Cube;
		//cube->transform(pos);
		m_shape_list.push_back(new Cube(pos));

		//m_shape_list.at(0)->transform(pos);
	}

	// 선택한 물체를 리스트에서 삭제한다
	void Delete_Objet()
	{
	}

	
	// 리스트의 모든 도형을 그려준다
	void DrawAll()
	{
		float delim = 0.7;

		for (int i = 0; i < m_shape_list.size(); i++)
		{
			m_shape_list.at(i)->Draw(m_camera);
			m_shape_list.at(i)->rotate(glm::vec3(m_cosCounter * 0.3f, m_sinCounter * 0.5f, 0));
			m_shape_list.at(i)->translate(glm::vec3(m_cosCounter*m_sinCounter * .03f *i, m_sinCounter*m_cosCounter * .05f *i, 0));
		}
	}
	
	// 카운터를 설정한다
	void SetCounter(float counter)
	{
		m_sinCounter = sinf(counter);	// sin counter
		m_cosCounter = cosf(counter);	// cos counter
	}
	
	// 초기화
	// 그리기를 위해서 cameara 정보 필요
	void Init(Camera* camera)
	{
		m_camera = camera;
	}

private:
	//QuadCore::Texture m_texture;
	//Shape* m_shape;
	std::vector<Shape*> m_shape_list;

	QuadCore::Camera* m_camera;

	typename glm::vec3 vec;

	float m_sinCounter;
	float m_cosCounter;
};

}

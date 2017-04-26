#pragma once

//#include "Texture.h"
#include "iShape.h"
#include <vector>

#include "Cube.h"
#include "BasicObject.h"

namespace QuadCore
{

class ShapeManager
{
public:
	ShapeManager() {}
	virtual ~ShapeManager() {}

	//// �⺻������ ��� ����ϴ� �׽�Ʈ �ڵ�
	void Insert_TestObjects()
	{
		for (int i = 0; i < BasicObject::FIGURE::NUM_FIGURE; i++)
		{
			m_shape_list.push_back(new BasicObject(glm::vec3( sinf(i)*13, -3, cosf(i)*13), i ));
		}
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�	
	// ��ü�� ����Ʈ�� �߰��Ѵ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Insert_Object(glm::vec3 pos /*= glm::vec3()*/)
	{
		m_shape_list.push_back(new BasicObject(pos, BasicObject::FIGURE::Cube));

		//m_shape_list.at(0)->transform(pos);
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// ������ ��ü�� ����Ʈ���� �����Ѵ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Delete_Objet()
	{
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//  ������ ��ü�� �ּҰ��� ��ȯ�Ѵ�.
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	iShape* GetObject(int index)
	{
		if (index<0 || index>m_shape_list.size() - 1)	// ����ó��
			return NULL;
		return m_shape_list.at(index);
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// ������ ��ü ����Ʈ�� �ּҰ��� ��ȯ�Ѵ�.
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	std::vector<iShape*> GetObjectList(int index)
	{
		return m_shape_list;
	}
	
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// ����Ʈ�� ��� ������ �׷��ش�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void DrawAll()
	{
		float delim = 0.7;

		for (int i = 0; i < m_shape_list.size(); i++)
		{
			m_shape_list.at(i)->Draw(m_camera);			
		}
	}
	
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// �ʱ�ȭ
	// �׸��⸦ ���ؼ� cameara ���� �ʿ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Init(Camera* camera)
	{
		m_camera = camera;
	}

private:
	//QuadCore::Texture m_texture;
	//Shape* m_shape;
	std::vector<iShape*> m_shape_list;

	QuadCore::Camera* m_camera;

	typename glm::vec3 vec;	
};

}

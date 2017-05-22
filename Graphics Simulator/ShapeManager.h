#pragma once

//#include "Texture.h"
#include "iShape.h"
#include <vector>

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
			m_shape_list.push_back(new BasicObject(glm::vec3( sinf((float)i)*13.0f, -3.0f, cosf((float)i)*13.0f), i ));
		}
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�	
	// ��ü�� ����Ʈ�� �߰��Ѵ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Insert_Object_BasicShape(glm::vec3 pos, int figure_num = BasicObject::FIGURE::Cube)
	{
		m_shape_list.push_back(new BasicObject(pos, figure_num));
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�	
	// ��ü�� ����Ʈ�� �߰��Ѵ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Insert_Object(iShape* shape)
	{
		m_shape_list.push_back(shape);
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// ������ ��ü�� ����Ʈ���� �����Ѵ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Delete_Objet(int index)
	{
		m_shape_list.erase(m_shape_list.begin()+index);
	}


	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// ������ ��ü�� ����Ʈ���� �����Ѵ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Modify_Objet(int index, iShape* shape)
	{
		m_shape_list.erase(m_shape_list.begin() + index);

		std::vector<iShape*>::iterator it = m_shape_list.begin();
		m_shape_list.insert(it, shape);

		//// ���� ������Ʈ�� �ٸ� �����Ϳ� ����
		//iShape* tShape = m_shape_list.at(index);

		//// ���� �����Ϳ� ���ο� ������Ʈ�� ����
		//m_shape_list.at(index) = shape;

		//// ���� ������Ʈ�� ����
		//delete(tShape);
		//tShape = NULL;
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
	//  ����Ʈ�� ������ ��ȯ�Ѵ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	int GetSize()
	{
		return (int)m_shape_list.size(); // size_t -> int ����ȯ �߻�, ���������� ����
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
	void DrawAll(bool local_coordinate = false, bool poly_mode = false)
	{
		float delim = 0.7f;

		for (int i = 0; i < m_shape_list.size(); i++)
		{
			m_shape_list.at(i)->Draw(m_camera, local_coordinate, poly_mode);
		}
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// ����Ʈ�� ��� ������ �׷��ش� (������ ��� ���ð���)
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void DrawAll_PolyMode(bool local_coordinate = false, bool poly_mode = false)
	{
		for (int i = 0; i < m_shape_list.size(); i++)
		{
			m_shape_list.at(i)->Draw(m_camera, local_coordinate, poly_mode);
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

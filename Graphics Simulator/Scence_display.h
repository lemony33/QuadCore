#pragma once

#include "iScene.h"


class Scence_display : public QuadCore::iScene
{
public:
	Scence_display()
	{
	}

	virtual ~Scence_display()
	{
	}

public:
	virtual void Animate()
	{
	}


private:
	virtual void Draw()
	{
		using QuadCore::BasicObject;
		using QuadCore::Transform;

		float radians = 90.0f * glm::pi<float>() / 180.0f;


		// �濡�� ������ ������ �߰�

		// �ó�����
		/*
			������Ʈ - lucy / lucycat / lucycat(�׹���)
					- tyra
			����Ʈ - ��������(�⺻) / ��-��������(�߰������ʿ�, �������� �߰��Ұ�) / ��Ƽ������
			�ؽ��� - 
		*/


		//float length = size / 2.0f;

		//float radians = 90.0f * glm::pi<float>() / 180.0f;

		//Transform* tTop = new Transform(glm::vec3(0.0f, +length, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(size, thickness, size));

		//BasicObject* objTop = new BasicObject("BasicObjects/Cube", "basicShader_multilight", "black_formula", tTop);

		//m_shape_manager.Insert_Object(objTop);

	}
};

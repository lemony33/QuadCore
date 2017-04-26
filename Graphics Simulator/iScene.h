#pragma once

#include "ShapeManager.h"


static float m_counter;
static float m_sinCounter;
static float m_cosCounter;


namespace QuadCore
{

class iScene
{
public:
	iScene() {}
	virtual ~iScene() {}

	/// ������ ����ϴ� �Լ�
public:
	// ī�޶� ����
	virtual void Init(Camera* camera)
	{
		m_shape_manager.Init(camera);
	}
	// �׷��� ������ ����Ѵ�
	virtual void Play() = 0;


	// ī���͸� �����Ѵ�
	static void SetCounter(float counter)
	{
		m_counter = counter;
		m_sinCounter = sinf(counter);	// sin counter
		m_cosCounter = cosf(counter);	// cos counter
	}
	

	/// ���������� �׸��� ������ ó��
protected:
	virtual void Draw() = 0;
	
protected:
	ShapeManager m_shape_manager;
};

}
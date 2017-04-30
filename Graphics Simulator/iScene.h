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
	// �ʱ�ȭ (ī�޶� ����, �׸��� ����)
	virtual void Init(Camera* camera)
	{
		m_shape_manager.Init(camera);
		Draw();
	}
	// �׷��� ������ ����Ѵ�
	virtual void Play()
	{
		if (!m_enable)
			return;

		Animate();

		m_shape_manager.DrawAll();
	}

	//���� ���޿� play �����ε� �Լ�. �� �Լ����� ������ ó���ϴ°� �ٸ� �� �����Ƿ� �ڽĿ��� �Լ� ���� ���ϵ���
	virtual void Play(int pos) {}

	// ī���͸� �����Ѵ�
	static void SetCounter(float counter)
	{
		m_counter = counter;
		m_sinCounter = sinf(counter);	// sin counter
		m_cosCounter = cosf(counter);	// cos counter
	}

	void SetEnable(bool enable)
	{
		m_enable = enable;
	}
	
	/// ���������� �׸��� ������ ó��
protected:
	virtual void Draw() = 0;
	virtual void Animate() = 0;
	
protected:
	ShapeManager m_shape_manager;
	bool m_enable = false;
};

}
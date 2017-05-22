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
	bool m_local_coordinate = false;
	void Set_LocalCoordinate(bool local_coordinate)
	{
		m_local_coordinate = local_coordinate;
	}

	// �׷��� ������ ����Ѵ�
	virtual void Play()
	{
		if (!m_enable)
			return;

		Animate();

		m_shape_manager.DrawAll(m_local_coordinate, m_poly_mode);
	}

	//���� ���޿� play �����ε� �Լ�. �� �Լ����� ������ ó���ϴ°� �ٸ� �� �����Ƿ� �ڽĿ��� �Լ� ���� ���ϵ���
	virtual void Play(int pos) {}
	virtual void Play(float speed, glm::vec3* pos, glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular) {}
	virtual void Play(float* g_rotation, float speed, glm::vec3* pos, glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular) {}

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

	bool m_poly_mode = false;
	void Set_PolyMode(bool poly_mode)
	{
		m_poly_mode = poly_mode;
	}

	virtual void Set_NormalMode(int normal_mode)
	{
	}
	virtual void Set_ObjectScale(float scale)
	{
	}
	virtual void Set_TesselMode(float level_inner, float level_outer, float level_scale)
	{
	}
	virtual void Set_RenderMode(int object_mode, int shader_mode, int texture_mode)
	{
	}
	virtual void Set_EffectMode(int effect_mode, bool flag)
	{
	}
	virtual void Sync_Value_Normal(float* num)
	{
	}
	virtual void Sync_Value_Explode_Speed(float* num)
	{
	}
	virtual void Sync_Value_Explode_Factor(float* num)
	{
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
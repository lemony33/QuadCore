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

	/// 실제로 사용하는 함수
public:
	// 초기화 (카메라 연결, 그리기 설정)
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

	// 그려진 내용을 재생한다
	virtual void Play()
	{
		if (!m_enable)
			return;

		Animate();

		m_shape_manager.DrawAll(m_local_coordinate, m_poly_mode);
	}

	//인자 전달용 play 오버로딩 함수. 각 함수마다 변수를 처리하는게 다를 수 있으므로 자식에서 함수 내용 정하도록
	virtual void Play(int pos) {}
	virtual void Play(float speed, glm::vec3* pos, glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular) {}
	virtual void Play(float* g_rotation, float speed, glm::vec3* pos, glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular) {}

	// 카운터를 설정한다
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
	
	/// 내부적으로 그리기 로직만 처리
protected:
	virtual void Draw() = 0;
	virtual void Animate() = 0;
	
protected:
	ShapeManager m_shape_manager;
	bool m_enable = false;
};

}
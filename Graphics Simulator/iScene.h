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
	// 그려진 내용을 재생한다
	virtual void Play()
	{
		if (!m_enable)
			return;

		Animate();

		m_shape_manager.DrawAll();
	}

	//인자 전달용 play 오버로딩 함수. 각 함수마다 변수를 처리하는게 다를 수 있으므로 자식에서 함수 내용 정하도록
	virtual void Play(int pos) {}

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
	
	/// 내부적으로 그리기 로직만 처리
protected:
	virtual void Draw() = 0;
	virtual void Animate() = 0;
	
protected:
	ShapeManager m_shape_manager;
	bool m_enable = false;
};

}
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
	// 카메라 연결
	virtual void Init(Camera* camera)
	{
		m_shape_manager.Init(camera);
	}
	// 그려진 내용을 재생한다
	virtual void Play() = 0;


	// 카운터를 설정한다
	static void SetCounter(float counter)
	{
		m_counter = counter;
		m_sinCounter = sinf(counter);	// sin counter
		m_cosCounter = cosf(counter);	// cos counter
	}
	

	/// 내부적으로 그리기 로직만 처리
protected:
	virtual void Draw() = 0;
	
protected:
	ShapeManager m_shape_manager;
};

}
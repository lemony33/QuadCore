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


		// 방에서 보여줄 컨텐츠 추가

		// 시나리오
		/*
			오브젝트 - lucy / lucycat / lucycat(그물형)
					- tyra
			라이트 - 퐁라이팅(기본) / 퐁-림라이팅(추가설정필요, 마지막에 추가할것) / 멀티라이팅
			텍스쳐 - 
		*/


		//float length = size / 2.0f;

		//float radians = 90.0f * glm::pi<float>() / 180.0f;

		//Transform* tTop = new Transform(glm::vec3(0.0f, +length, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(size, thickness, size));

		//BasicObject* objTop = new BasicObject("BasicObjects/Cube", "basicShader_multilight", "black_formula", tTop);

		//m_shape_manager.Insert_Object(objTop);

	}
};

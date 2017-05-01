#pragma once


#include "iScene.h"


class Scence_reflect_shader : public QuadCore::iScene
{
public:

	Scence_reflect_shader()
	{
	}

	virtual ~Scence_reflect_shader()
	{
	}

public:
	virtual void Animate()
	{
		float y_pos = m_height - m_counter*m_counter;
		if (y_pos > 0)
		{
			for (float degree = 0.0f; degree <= 90.0f; degree+=0.1f)
			{
				float radian = degree * glm::pi<float>() / 180.0f;
				glassTrans->GetPos().y = y_pos*sinf(radian);
				mirrorTrans->GetPos().y = y_pos*sinf(radian);
			}
		}
	}

private:
	virtual void Draw()
	{
		using QuadCore::BasicObject;
		using QuadCore::Transform;

		glassTrans = new Transform(glm::vec3(10.0, m_height, 0));
		mirrorTrans = new Transform(glm::vec3(-10.0, m_height, 0));

		BasicObject* glass = new BasicObject("nanosuit_reflection/nanosuit", "nanosuit/glass", "bricks", glassTrans);
		BasicObject* mirror = new BasicObject("nanosuit_reflection/nanosuit", "nanosuit/mirror", "bricks", mirrorTrans);
		m_shape_manager.Insert_Object(glass);
		m_shape_manager.Insert_Object(mirror);
	}

private:
	QuadCore::Transform* glassTrans;
	QuadCore::Transform* mirrorTrans;

	float m_height = 50.0f;
};


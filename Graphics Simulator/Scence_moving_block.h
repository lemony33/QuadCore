#pragma once


#include "iScene.h"


class Scence_moving_block : public QuadCore::iScene
{
public:

	Scence_moving_block()
	{
		Draw();
	}

	virtual ~Scence_moving_block()
	{
	}

public:
	virtual void Play()
	{
		for (int i = 0; i < 6; i++)
		{
			m_shape_manager.GetObject(i)->rotate(glm::vec3(m_cosCounter * 0.3f, m_sinCounter * 0.5f, 0));
			m_shape_manager.GetObject(i)->translate(glm::vec3(m_cosCounter*m_sinCounter * .03f *i, m_sinCounter*m_cosCounter * .05f *i, 0));
		}
		m_shape_manager.DrawAll();
	}

private:
	virtual void Draw()
	{
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(1, 1, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(2, 2, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(3, 3, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(4, 4, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(5, 5, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(1, 5, 3));
	}
};


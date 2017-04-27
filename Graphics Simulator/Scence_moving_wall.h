#pragma once


#include "iScene.h"


class Scence_moving_wall : public QuadCore::iScene
{
public:

	Scence_moving_wall()
	{
	}

	virtual ~Scence_moving_wall()
	{
	}

public:
	virtual void Animate()
	{
		for (int i = 0; i < 9; i++)
		{
			m_shape_manager.GetObject(i)->translate(glm::vec3(0, 0, m_sinCounter*.01 - 0.15*m_cosCounter));
		}
	}

private:
	virtual void Draw()
	{
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(-1, -1, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(0, -1, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(1, -1, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(-1, 1, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(0, 1, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(1, 1, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(-1, 0, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(0, 0, 0));
		m_shape_manager.Insert_Object_BasicShape(glm::vec3(1, 0, 0));
	}
};


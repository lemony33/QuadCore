#pragma once

#include "iScene.h"


class Scene_basicObjects : public QuadCore::iScene
{
public:
	Scene_basicObjects()
	{
	}

	virtual ~Scene_basicObjects()
	{
	}

public:
	virtual void Animate()
	{
		float radius = 9.0f;
		for (int i = 0; i < m_shape_manager.GetSize(); i++)
		{			
			//m_shape_manager.GetObject(i)->translate(glm::vec3(sinf(m_counter), m_sinCounter*m_cosCounter*.005*i * m_counter, cosf(m_counter)));
			m_shape_manager.GetObject(i)->position(glm::vec3((float)sinf(m_counter*.1f + i)*radius, (float)sinf(m_counter + i)*(float)cosf(m_counter + i), (float)cosf(m_counter*.1f + i)*radius));
			m_shape_manager.GetObject(i)->rotate(glm::vec3(0, m_counter, 0));
		}
	}

private:
	virtual void Draw()
	{
		m_shape_manager.Insert_TestObjects();
	}

};


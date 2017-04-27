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
		for (int i = 0; i < m_shape_manager.GetSize(); i++)
		{
			m_shape_manager.GetObject(i)->translate(glm::vec3(0, m_sinCounter*m_cosCounter*.005*i, 0));
			m_shape_manager.GetObject(i)->rotate(glm::vec3(0, m_counter, 0));
		}
	}

private:
	virtual void Draw()
	{
		m_shape_manager.Insert_TestObjects();
	}

};


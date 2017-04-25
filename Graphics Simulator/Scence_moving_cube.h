#pragma once

#include "iScene.h"


class Scence_moving_cube : public QuadCore::iScene
{
public:

	Scence_moving_cube()
	{
		Draw();
	}

	virtual ~Scence_moving_cube()
	{
	}

public:
	virtual void Play()
	{
		float delim = 0.7;

		m_shape_manager.GetObject(0)->position(glm::vec3(1.1, 1.1, 0));
		m_shape_manager.GetObject(0)->translate(glm::vec3(delim * m_cosCounter, delim * m_sinCounter,0) );
		m_shape_manager.GetObject(0)->rotate(glm::vec3(m_counter * 0.3f, m_counter * 0.5f, 0));

		m_shape_manager.GetObject(1)->position(glm::vec3(-1.1, 0, 0));
		m_shape_manager.GetObject(1)->translate(glm::vec3(delim * sinf(m_counter), delim * cosf(m_counter), 0));
		m_shape_manager.GetObject(1)->rotate(glm::vec3(m_counter * 0.3f, m_counter * 0.5f, 0));

		float r = 3.0f;
		m_shape_manager.GetObject(2)->position(glm::vec3(-r / 2.0f, 0, 0));	// icosphere
		m_shape_manager.GetObject(2)->translate(glm::vec3(sinf(m_counter) * r, cosf(m_counter) * r, 0/* tanf(m_counter) * r*/));
		m_shape_manager.GetObject(2)->rotate(glm::vec3(m_counter * 0.7f, m_counter * 0.9f, 0));		
		
		m_shape_manager.DrawAll();
	}

private:
	virtual void Draw()
	{
		///
		m_shape_manager.Insert_Object(glm::vec3(1.1, 1.1, 0));		// cube - right side
		m_shape_manager.Insert_Object(glm::vec3(-1.1, 0, 0));		// cube - left side

		float r = 3.0f;
		m_shape_manager.Insert_Object(glm::vec3(-r / 2.0f, 0, 0));	// icosphere
	}
};

#pragma once

#include "iScene.h"


class Scence_moving_cube : public QuadCore::iScene
{
public:

	Scence_moving_cube()
	{
	}

	virtual ~Scence_moving_cube()
	{
	}

public:
	virtual void Animate()
	{
		m_shape_manager.GetObject(0)->position(glm::vec3(1.1, 1.1, 0));
		m_shape_manager.GetObject(0)->translate(glm::vec3(delim * m_cosCounter, delim * m_sinCounter,0) );
		m_shape_manager.GetObject(0)->rotate(glm::vec3(m_counter * 0.3f, m_counter * 0.5f, 0));

		m_shape_manager.GetObject(1)->position(glm::vec3(-1.1, 0, 0));
		m_shape_manager.GetObject(1)->translate(glm::vec3(delim * sinf(m_counter), delim * cosf(m_counter), 0));
		m_shape_manager.GetObject(1)->rotate(glm::vec3(m_counter * 0.3f, m_counter * 0.5f, 0));

		m_shape_manager.GetObject(2)->position(glm::vec3(-r / 2.0f, 0, 0));	// icosphere
		m_shape_manager.GetObject(2)->translate(glm::vec3(sinf(m_counter) * r, cosf(m_counter) * r, 0/* tanf(m_counter) * r*/));
		m_shape_manager.GetObject(2)->rotate(glm::vec3(m_counter * 0.7f, m_counter * 0.9f, 0));	
	}

private:
	virtual void Draw()
	{		
		using QuadCore::BasicObject;
		using QuadCore::Transform;
		
		// cube - right side
		Transform* transform1 = new Transform(glm::vec3(1.1, 1.1, 0));
		BasicObject* object1 = new BasicObject("BasicObjects/Cube", "basicShader_light", "bricks", transform1);
		m_shape_manager.Insert_Object(object1);		

		// cube - left side
		Transform* transform2 = new Transform(glm::vec3(-1.1, 0, 0));
		BasicObject* object2 = new BasicObject("BasicObjects/Cube", "basicShader_light", "bricks", transform2);
		m_shape_manager.Insert_Object(object2);		

		// Icosphere
		Transform* transform3 = new Transform(glm::vec3(-r / 2.0f, 0, 0));
		BasicObject* object3 = new BasicObject("BasicObjects/Icosphere", "basicShader_light", "bricks", transform3);
		m_shape_manager.Insert_Object(object3);		
		
		//m_shape_manager.Delete_Objet(0); // 제거방법
	}

private:
	float delim = 0.7f;
	float r = 3.0f;
};

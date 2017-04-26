#pragma once


#include "iScene.h"


class Scence_reflect_shader : public QuadCore::iScene
{
public:

	Scence_reflect_shader()
	{
		Draw();
	}

	virtual ~Scence_reflect_shader()
	{
	}

public:
	virtual void Play()
	{
		
		m_shape_manager.DrawAll();
	}

private:
	virtual void Draw()
	{
		using QuadCore::BasicObject;
		using QuadCore::Transform;

		Transform* glassTrans = new Transform(glm::vec3(10.0, 0, 0));
		Transform* mirrorTrans = new Transform(glm::vec3(-10.0, 0, 0));

		BasicObject* glass = new BasicObject("nanosuit_reflection/nanosuit", "../shaders/cubemaps/glass", "bricks", glassTrans);
		BasicObject* mirror = new BasicObject("nanosuit_reflection/nanosuit", "../shaders/cubemaps/mirror", "bricks", mirrorTrans);
		m_shape_manager.Insert_Object(glass);
		m_shape_manager.Insert_Object(mirror);
	}
};


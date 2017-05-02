#pragma once

#include "iScene.h"


class Scene_room : public QuadCore::iScene
{
public:
	Scene_room()
	{
	}

	virtual ~Scene_room()
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

		////// cube - right side
		//Transform* transform1 = new Transform(glm::vec3(1.1, 1.1, 0));
		//transform1->SetScale(glm::vec3(50.0f, 50.0f, 50.0f));
		//BasicObject* object1 = new BasicObject("RoomCube", "basicShader_light", "bricks", transform1);
		//m_shape_manager.Insert_Object(object1);

		//Transform* transform2 = new Transform(glm::vec3(0.0f, 0.0f, 60.0f));
		//BasicObject* object2 = new BasicObject("Cube", "lamp", "bricks", transform2);
		//m_shape_manager.Insert_Object(object2);

		
		float length = size / 2.0f;

		float radians = 90.0f * glm::pi<float>() / 180.0f;

		Transform* tTop		= new Transform(glm::vec3(0.0f, +length, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(size, thickness, size));
		Transform* tBottom	= new Transform(glm::vec3(0.0f, -length, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(size, thickness, size));
		Transform* tLeft	= new Transform(glm::vec3(-length, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, radians), glm::vec3(size, thickness, size));
		Transform* tRight	= new Transform(glm::vec3(+length, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, radians), glm::vec3(size, thickness, size));
		Transform* tBack	= new Transform(glm::vec3(0.0f, 0.0f, -length), glm::vec3(radians, 0.0f, 0.0f), glm::vec3(size, thickness, size));
		Transform* tFront	= new Transform(glm::vec3(0.0f, 0.0f, +length), glm::vec3(radians, 0.0f, 0.0f), glm::vec3(size, thickness, size));

		BasicObject* objTop = new BasicObject("BasicObjects/Cube", "basicShader_light", "black_formula", tTop);
		BasicObject* objBottom = new BasicObject("BasicObjects/Cube", "basicShader_light", "black_formula", tBottom);
		BasicObject* objLeft = new BasicObject("BasicObjects/Cube", "basicShader_light", "black_formula", tLeft);
		BasicObject* objRight = new BasicObject("BasicObjects/Cube", "basicShader_light", "black_formula", tRight);
		BasicObject* objBack = new BasicObject("BasicObjects/Cube", "basicShader_light", "black_formula", tBack);
		BasicObject* objFront = new BasicObject("BasicObjects/Cube", "basicShader_light", "black_formula", tFront);

		m_shape_manager.Insert_Object(objTop);
		m_shape_manager.Insert_Object(objBottom);
		m_shape_manager.Insert_Object(objLeft);
		m_shape_manager.Insert_Object(objRight);
		m_shape_manager.Insert_Object(objBack);
		m_shape_manager.Insert_Object(objFront);
		

		//using QuadCore::iShape;
		//iShape* room = new Room("skybox");
		//m_shape_manager.Insert_Object(room);
	}

private:
	const float thickness = 0.3f;
	const float size = 100.0f;
};

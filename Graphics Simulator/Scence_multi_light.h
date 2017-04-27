#pragma once


#include "iScene.h"

using QuadCore::Transform;

class Scence_multi_light : public QuadCore::iScene
{
public:

	Scence_multi_light()
	{
	}

	virtual ~Scence_multi_light()
	{
	}

public:
	virtual void Animate()
	{
		lightTransforms[0].Init(glm::vec3(1.0f * sinf(m_counter / 10), 0, 1.0f * cosf(m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[1].Init(glm::vec3(1.0f * cos(m_counter / 10), 1.0f * sinf(m_counter / 10), 0), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[2].Init(glm::vec3(0, 1.0f * cos(m_counter / 10), 1.0f * sinf(m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[3].Init(glm::vec3(5.0f * sinf(-m_counter / 10), 0, 5.0f * cosf(-m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));

		for(int i = 0; i < 5; i++)
		m_shape_manager.GetObject(i)->GetShader()->InputpointLight(lightTransforms, ambient, diffuse, specular);
	}

private:
	virtual void Draw()
	{
		using QuadCore::BasicObject;
		using QuadCore::Transform;

		//// multiLight		
		Transform* multitest = new Transform(glm::vec3(0, 0.0f, 0), glm::vec3(), glm::vec3(1.0f));
		BasicObject* object = new BasicObject("BasicObjects/Sphere", "basicShader_multilight", "moon", multitest);
		m_shape_manager.Insert_Object(object);

		for (int i = 0; i < 4; i++)
		{
			BasicObject* light = new BasicObject("BasicObjects/Cube", "lamp", "moon", &lightTransforms[i]);
			m_shape_manager.Insert_Object(light);
		}
	}

private:
	// multiLight
	Transform lightTransforms[4];

	glm::vec3 ambient[4] =
	{
		glm::vec3(0.05f, 0.05f, 0.05f),
		glm::vec3(0.05f, 0.05f, 0.05f),
		glm::vec3(0.05f, 0.05f, 0.05f),
		glm::vec3(0.05f, 0.05f, 0.05f),
	};
	glm::vec3 diffuse[4] =
	{
		glm::vec3(0.8f, 0.4f, 0.4f),
		glm::vec3(0.4f, 0.8f, 0.4f),
		glm::vec3(0.4f, 0.4f, 0.8f),
		glm::vec3(0.8f, 0.8f, 0.8f),
	};
	glm::vec3 specular[4] =
	{
		glm::vec3(1.0f, 0.5f, 0.5f),
		glm::vec3(0.5f, 1.0f, 0.5f),
		glm::vec3(0.5f, 0.5f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
	};
};


#pragma once

#define LIMIT 128
#include "iScene.h"

using QuadCore::Transform;

class Scence_mirror : public QuadCore::iScene
{
public:

	Scence_mirror()
	{
		Draw();
	}

	virtual ~Scence_mirror()
	{
	}

public:
	virtual void Animate()
	{
		for (int i = 0; i < subSphereNum; i++)
		{
			MirrorSphere[i].Init(glm::vec3(5 * sinf((m_counter + i * 0.2f) / 5) * cosf(-(m_counter + i * 0.2f) / 5),
				5 * sinf(-(m_counter + i * 0.2f) / 5),
				5 * cosf((m_counter + i * 0.2f) / 5) * cosf(-(m_counter + i * 0.2f) / 5)),
				glm::vec3(),
				glm::vec3(0.5f, 0.5f, 0.5f)
			);
		}
		m_shape_manager.DrawAll();
	}

private:
	virtual void Draw()
	{
		using QuadCore::BasicObject;
		using QuadCore::Transform;

		for (int i = 0; i < subSphereNum; i++)
		{
			BasicObject* light = new BasicObject("BasicObjects/Sphere", "nanosuit/glass", "solarsystem/moon", &MirrorSphere[i]);
			m_shape_manager.Insert_Object(light);
		}
	}

private:
	//mirror
	int subSphereNum = 64;
	Transform mainSphere;
	Transform MirrorSphere[LIMIT];
	
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


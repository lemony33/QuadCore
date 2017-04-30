#pragma once

#define LIMIT 32
#include "iScene.h"

using QuadCore::Transform;

class Scence_mirror : public QuadCore::iScene
{
public:

	Scence_mirror()
	{
	}

	virtual ~Scence_mirror()
	{
	}

private:
	char m_key = 0;
public:
	bool KeyInput(char key)
	{
		printf("KeyInput: %c, ", key);
		if (key == NULL)
			return false;
		if (key != '+' || key != '-')
			return false;

		m_key = key;
		return true;
	}
	char Get_KeyInput()
	{
		printf("GetKey: %d \n", subSphereNum);
		if (m_key == NULL)
			return false;

		char key = m_key;
		m_key = NULL;
		return key;
	}
	virtual void Play(int pos)
	{
		if (!m_enable)
			return;
		if(pos != 0)
			subSphereNum = pos;

		Animate();

		m_shape_manager.DrawAll();
	}

	virtual void Animate()
	{
		if (Get_KeyInput())
		{
			printf(" / cur_num: %d \n", subSphereNum);
			if(m_key=='+')
				subSphereNum++;
			if (m_key == '-')
				subSphereNum--;
		}
		for (int i = 0; i < subSphereNum; i++)
		{
			MirrorSphere[i].Init(glm::vec3(5 * sinf((m_counter + i * 0.2f) / 5) * cosf(-(m_counter + i * 0.2f) / 5),
				5 * sinf(-(m_counter + i * 0.2f) / 5),
				5 * cosf((m_counter + i * 0.2f) / 5) * cosf(-(m_counter + i * 0.2f) / 5)),
				glm::vec3(),
				glm::vec3(0.5f, 0.5f, 0.5f)
			);
		}
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
	int subSphereNum = 32;
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


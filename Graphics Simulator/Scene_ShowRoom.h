#pragma once

#include "iScene.h"


class Scene_ShowRoom : public QuadCore::iScene
{
public:
	Scene_ShowRoom()
	{
	}

	virtual ~Scene_ShowRoom()
	{
	}

public:
	virtual void Play(float speed, glm::vec3* pos, glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular)
	{
		if (!m_enable)
			return;
		//if (speed < 0.01) this->speed = 0.01f;
		//else if (speed > 2.0) this->speed = 2.0f;
		//else this->speed = speed;
		//printf("rotspeed = %f\n", this->speed);
		rot += speed*0.1f;
		if (rot > 2.0f*glm::pi<float>())
			rot = 0.0f;
		multitest->SetRot(glm::vec3(0, rot, 0));

		for (int i = 0; i < 3; i++)
		{
			lightTransforms[i + 1].SetPos(pos[i]);
			lightTransforms[i + 1].SetRot(glm::vec3(0, m_counter / 0.5f  * speed, 0));
			lightTransforms[i + 1].SetScale(glm::vec3(0.3f, 0.2f + 0.1f * sinf(m_counter * speed * 20.0f), 0.3f));
			this->ambient[i + 1] = ambient[i];
			this->diffuse[i + 1] = diffuse[i];
			this->specular[i + 1] = specular[i];

		}

		Animate();

		m_shape_manager.DrawAll();
	}

public:
	virtual void Animate()
	{
		lightTransforms[0].Init(glm::vec3(1.0f * sinf(m_counter / 10), 0, 1.0f * cosf(m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[1].Init(glm::vec3(1.0f * cos(m_counter / 10), 1.0f * sinf(m_counter / 10), 0), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[2].Init(glm::vec3(0, 1.0f * cos(m_counter / 10), 1.0f * sinf(m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[3].Init(glm::vec3(5.0f * sinf(-m_counter / 10), 0, 5.0f * cosf(-m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));

		for (int i = 0; i < 5; i++)
			m_shape_manager.GetObject(i)->GetShader()->InputpointLight(lightTransforms, ambient, diffuse, specular);
	}

private:
	virtual void Draw()
	{
		using QuadCore::BasicObject;
		using QuadCore::Transform;

		//// multiLight		
		multitest = new Transform(glm::vec3(0, 0.0f, 0), glm::vec3(), glm::vec3(30.0f));
		object = new BasicObject("test/half_lucy", "basicShader_multilight_prev", "bricks", multitest);
		m_shape_manager.Insert_Object(object);

		for (int i = 0; i < 4; i++)
		{
			BasicObject* light = new BasicObject("test/octahedron", "lamp_prev", "moon", &lightTransforms[i]);
			m_shape_manager.Insert_Object(light);
		}
	}

private:
	Transform* multitest;
	QuadCore::BasicObject* object;

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

	//float speed = 0.1f; // 공전주기 속도 비율
	float rot = 0.0f;
};

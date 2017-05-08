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
	virtual void Play(float* g_rotation, float speed, glm::vec3* pos, glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular)
	{
		if (!m_enable)
			return;
		//if (speed < 0.01) this->speed = 0.01f;
		//else if (speed > 2.0) this->speed = 2.0f;
		//else this->speed = speed;
		//printf("rotspeed = %f\n", this->speed);
		rot += speed*0.01f;
		if (rot > 2.0f*glm::pi<float>())
			rot = 0.0f;
		//transform_obj->SetRot(glm::vec3(0, rot, 0));



		//if (prev_rot[0] == g_rotation[0])
		//{
		//	g_rotation[0] -= 0.01f;
		//	if (g_rotation[0] < 0)
		//		g_rotation[0] = 0.0f;
		//}
		//if (prev_rot[1] == g_rotation[1])
		//{
		//	g_rotation[1] -= 0.01f;
		//	if (g_rotation[1] < 0)
		//		g_rotation[1] = 0.0f;
		//}
		//if (prev_rot[2] == g_rotation[2])
		//{
		//	g_rotation[2] -= 0.01f;
		//	if (g_rotation[2] < 0)
		//		g_rotation[2] = 0.0f;
		//}


		float radians[3] = {
			g_rotation[0] * glm::pi<float>(),	// / 180.0f
			g_rotation[1] * glm::pi<float>(),
			g_rotation[2] * glm::pi<float>(),
		};


		printf(" ( %02f , %02f , %02f )", g_rotation[0], g_rotation[1], g_rotation[2]);
		transform_obj->SetRot(glm::vec3(radians[0], radians[1] + rot, radians[2]));

		prev_rot[0] = g_rotation[0];
		prev_rot[1] = g_rotation[1];
		prev_rot[2] = g_rotation[2];


		for (int i = 0; i < 3; i++)
		{
			lightTransforms[i].SetPos(pos[i]);
			lightTransforms[i].SetRot(glm::vec3(0, m_counter / 0.5f  * speed, 0));
			lightTransforms[i].SetScale(glm::vec3(0.3f, 0.2f + 0.1f * sinf(m_counter * speed * 20.0f), 0.3f));
			this->ambient[i] = ambient[i];
			this->diffuse[i] = diffuse[i];
			this->specular[i] = specular[i];

		}

		Animate();

		m_shape_manager.DrawAll(m_local_coordinate);
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
		//multitest = new Transform(glm::vec3(0, 0.0f, 0), glm::vec3(), glm::vec3(1.0f));
		//object = new BasicObject("Voronoi_Lucy", "basicShader_multilight_prev", "bricks", multitest);

		//multitest = new Transform(glm::vec3(0, -1.0f, 0), glm::vec3(), glm::vec3(50.0f));
		//object = new BasicObject("test/half_lucy", "basicShader_multilight_prev", "bricks", multitest);

		//multitest = new Transform(glm::vec3(0, -2.0f, 0), glm::vec3(), glm::vec3(20.0f));
		//object = new BasicObject("bunny", "basicShader_multilight_prev", "bricks", multitest);
		
		//transform_obj = new Transform(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(20.0f));
		////transform_obj = new Transform(glm::vec3(0, -2.0f, 0), glm::vec3(), glm::vec3(20.0f));
		//object = new BasicObject("bunny", "multi-PhongRim", "skyblue", transform_obj);


		transform_obj = new Transform(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(1.0f));
		object = new BasicObject("BasicObjects/Cube", "multi-PhongRim", "skyblue", transform_obj);

		m_shape_manager.Insert_Object(object);

		for (int i = 0; i < 4; i++)
		{
			BasicObject* light = new BasicObject("test/octahedron", "lamp_prev", "moon", &lightTransforms[i]);
			m_shape_manager.Insert_Object(light);
		}
	}

private:
	Transform* transform_obj;
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
		//glm::vec3(0.8f, 0.4f, 0.4f),
		//glm::vec3(0.4f, 0.8f, 0.4f),
		//glm::vec3(0.4f, 0.4f, 0.8f),
		//glm::vec3(0.8f, 0.8f, 0.8f),
		glm::vec3(1.0f, 0.4f, 0.4f),
		glm::vec3(0.4f, 1.0f, 0.4f),
		glm::vec3(0.4f, 0.4f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
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

	float prev_rot[3] = {};
	//float curr_rot[3] = {};
};

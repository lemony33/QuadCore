#pragma once

#define LIMIT 256
#include "iScene.h"

using QuadCore::Transform;

class Scence_SolarSystem : public QuadCore::iScene
{
public:

	Scence_SolarSystem()
	{
		Draw();
	}

	virtual ~Scence_SolarSystem()
	{
	}

public:
	virtual void Play()
	{
		//�༺��
		SunSphere.Init(glm::vec3(0.0f),
			glm::vec3(0.0f),
			glm::vec3(109.0f / 40.0f)); // �¾�

		MercurySphere.Init(glm::vec3(0.0f + 0.4 * distance * sinf(m_counter * 0.24f * speed),
									0.0f,
									0.0f + 0.4 * distance * cosf(m_counter * 0.24f * speed)),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.4f)); // ����

		VenusSphere.Init(glm::vec3(0.0f + 0.7 * distance * sinf(m_counter * 0.62f * speed),
									0.0f,
									0.0f + 0.7 * distance * cosf(m_counter * 0.62f * speed)),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.9f)); // �ݼ�

		EarthSphere.Init(glm::vec3(0.0f + 1.0 * distance * sinf(m_counter * 1.0f * speed),
									0.0f,
									0.0f + 1.0 * distance * cosf(m_counter * 1.0f * speed)),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f)); // ����

		MarsSphere.Init(glm::vec3(0.0f + 1.5 * distance * sinf(m_counter * 1.88f * speed),
									0.0f,
									0.0f + 1.5 * distance * cosf(m_counter * 1.88f * speed)),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.6f)); // ȭ��

		JupiterSphere.Init(glm::vec3(0.0f + 5.2 * distance * sinf(m_counter * 11.86f * speed) / 2.0f,
									0.0f,
									0.0f + 5.2 * distance * cosf(m_counter * 11.86f * speed) / 2.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(11.2f / 5.0f)); // ��

		SaturnSphere.Init(glm::vec3(0.0f + 9.5 * distance * sinf(m_counter * 29.46f * speed) / 3.0f,
									0.0f,
									0.0f + 9.5 * distance * cosf(m_counter * 29.46f * speed) / 3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(9.4f / 5.0f)); // �伺
		UranusSphere.Init(glm::vec3(0.0f + 19.2 * distance * sinf(m_counter * 84.07f * speed / 6.0f) / 4.0f,
									0.0f,
									0.0f + 19.2 * distance * cosf(m_counter * 84.07f * speed / 6.0f) / 4.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(4.0f / 3.0f)); // õ�ռ�

		NeptuneSphere.Init(glm::vec3(0.0f + 30.1 * distance * sinf(m_counter * 164.8f * speed / 2.0f) / 5.0f,
									0.0f,
									0.0f + 30.1 * distance * cosf(m_counter * 164.8f * speed / 2.0f) / 5.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(3.9f / 2.0f)); // �ؿռ�


		lightTransforms[0].Init(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[1].Init(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[2].Init(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[3].Init(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));

		for(int i = 0; i < 5; i++)
		m_shape_manager.GetObject(i)->GetShader()->InputpointLight(lightTransforms, ambient, diffuse, specular);

		m_shape_manager.DrawAll();
	}

private:
	virtual void Draw()
	{
		using QuadCore::BasicObject;
		using QuadCore::Transform;

		BasicObject* Sun_object = new BasicObject("Sphere", "basicShader_solarsystem", "solarsystem/sun", &SunSphere);
		m_shape_manager.Insert_Object(Sun_object);
		BasicObject* Mercury_object = new BasicObject("Sphere", "basicShader_solarsystem", "solarsystem/mercury", &MercurySphere);
		m_shape_manager.Insert_Object(Mercury_object);
		BasicObject* Venus_object = new BasicObject("Sphere", "basicShader_solarsystem", "solarsystem/venus", &VenusSphere);
		m_shape_manager.Insert_Object(Venus_object);
		BasicObject* Earth_object = new BasicObject("Sphere", "basicShader_solarsystem", "solarsystem/earth", &EarthSphere);
		m_shape_manager.Insert_Object(Earth_object);
		BasicObject* Mars_object = new BasicObject("Sphere", "basicShader_solarsystem", "solarsystem/mars", &MarsSphere);
		m_shape_manager.Insert_Object(Mars_object);
		BasicObject* Jupiter_object = new BasicObject("Sphere", "basicShader_solarsystem", "solarsystem/jupiter", &JupiterSphere);
		m_shape_manager.Insert_Object(Jupiter_object);
		BasicObject* Saturn_object = new BasicObject("Sphere", "basicShader_solarsystem", "solarsystem/saturn", &SaturnSphere);
		m_shape_manager.Insert_Object(Saturn_object);
		BasicObject* Uranus_object = new BasicObject("Sphere", "basicShader_solarsystem", "solarsystem/uranus", &UranusSphere);
		m_shape_manager.Insert_Object(Uranus_object);
		BasicObject* Neptune_object = new BasicObject("Sphere", "basicShader_solarsystem", "solarsystem/neptune", &NeptuneSphere);
		m_shape_manager.Insert_Object(Neptune_object);


		//Sky _ mirror
		/*BasicObject* main_object = new BasicObject("Sphere", "basicShader_multilight", "earth", &mainSphere);
		m_shape_manager.Insert_Object(main_object);
		for (int i = 0; i < subSphereNum; i++)
		{
			BasicObject* light = new BasicObject("Sphere", "basicShader_multilight", "moon", &subSphere[i]);
			m_shape_manager.Insert_Object(light);
		}
*/
		//// multiLight		
		/*Transform* multitest = new Transform(glm::vec3(0, 0.0f, 0), glm::vec3(), glm::vec3(1.0f));
		BasicObject* object = new BasicObject("Sphere", "basicShader_multilight", "moon", multitest);
		m_shape_manager.Insert_Object(object);

		for (int i = 0; i < 4; i++)
		{
			BasicObject* light = new BasicObject("Cube", "lamp", "moon", &lightTransforms[i]);
			m_shape_manager.Insert_Object(light);
		}*/
	}

private:
	//mirror
	int subSphereNum = 128;
	float distance = 5.0f; // �༺�� �Ÿ� �� ũ�� ����
	float speed = 0.01f; // �����ֱ� �ӵ� ����
	Transform SunSphere; // �¾�
	Transform MercurySphere; // ����
	Transform VenusSphere; // �ݼ�
	Transform EarthSphere; // ����
	Transform MarsSphere; // ȭ��
	Transform JupiterSphere; // ��
	Transform SaturnSphere; // �伺
	Transform UranusSphere; // õ�ռ�
	Transform NeptuneSphere; // �ؿռ�

	Transform mainSphere;
	Transform subSphere[LIMIT];
	Transform MirrorSphere[LIMIT];
	
	// multiLight
	Transform lightTransforms[4];

	glm::vec3 ambient[4] =
	{
		glm::vec3(0.35f, 0.35f, 0.35f),
		glm::vec3(0.05f, 0.05f, 0.05f),
		glm::vec3(0.05f, 0.05f, 0.05f),
		glm::vec3(0.05f, 0.05f, 0.05f),
	};
	glm::vec3 diffuse[4] =
	{
		glm::vec3(0.8f, 0.8f, 0.8f),
		glm::vec3(0.8f, 0.8f, 0.8f),
		glm::vec3(0.8f, 0.8f, 0.8f),
		glm::vec3(0.8f, 0.8f, 0.8f),
	};
	glm::vec3 specular[4] =
	{
		glm::vec3(0.8f, 0.8f, 0.8f),
		glm::vec3(0.8f, 0.8f, 0.8f),
		glm::vec3(0.8f, 0.8f, 0.8f),
		glm::vec3(0.8f, 0.8f, 0.8f),
	};
};


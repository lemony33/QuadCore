#pragma once

#define LIMIT 128
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
	virtual void Animate()
	{
		//행성계
		SunSphere.Init(glm::vec3(0.0f),
			glm::vec3(0.0f),
			glm::vec3(109.0f / 40.0f)); // 태양

		MercurySphere.Init(glm::vec3(0.0f + 0.4 * distance * sinf(m_counter * 0.24f * speed),
									0.0f,
									0.0f + 0.4 * distance * cosf(m_counter * 0.24f * speed)),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.4f)); // 수성

		VenusSphere.Init(glm::vec3(0.0f + 0.7 * distance * sinf(m_counter * 0.62f * speed),
									0.0f,
									0.0f + 0.7 * distance * cosf(m_counter * 0.62f * speed)),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.9f)); // 금성

		EarthSphere.Init(glm::vec3(0.0f + 1.0 * distance * sinf(m_counter * 1.0f * speed),
									0.0f,
									0.0f + 1.0 * distance * cosf(m_counter * 1.0f * speed)),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f)); // 지구

		MarsSphere.Init(glm::vec3(0.0f + 1.5 * distance * sinf(m_counter * 1.88f * speed),
									0.0f,
									0.0f + 1.5 * distance * cosf(m_counter * 1.88f * speed)),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.6f)); // 화성

		JupiterSphere.Init(glm::vec3(0.0f + 5.2 * distance * sinf(m_counter * 11.86f * speed) / 2.0f,
									0.0f,
									0.0f + 5.2 * distance * cosf(m_counter * 11.86f * speed) / 2.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(11.2f / 5.0f)); // 목성

		SaturnSphere.Init(glm::vec3(0.0f + 9.5 * distance * sinf(m_counter * 29.46f * speed) / 4.0f,
									0.0f,
									0.0f + 9.5 * distance * cosf(m_counter * 29.46f * speed) / 4.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(9.4f / 5.0f)); // 토성
		UranusSphere.Init(glm::vec3(0.0f + 19.2 * distance * sinf(m_counter * 84.07f * speed / 8.0f) / 6.0f,
									0.0f,
									0.0f + 19.2 * distance * cosf(m_counter * 84.07f * speed / 8.0f) / 6.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(4.0f / 3.0f)); // 천왕성

		NeptuneSphere.Init(glm::vec3(0.0f + 30.1 * distance * sinf(m_counter * 164.8f * speed / 10.0f) / 7.0f,
									0.0f,
									0.0f + 30.1 * distance * cosf(m_counter * 164.8f * speed / 10.0f) / 7.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(3.9f / 2.0f)); // 해왕성

		MoonSphere.Init(glm::vec3(EarthSphere.GetPos().x + 1.0f * distance * sinf(m_counter * 365.0f * speed / 10.0f) / 7.0f,
									0.0f,
									EarthSphere.GetPos().z + 1.0f * distance * cosf(m_counter * 365.0f * speed / 10.0f) / 7.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.1f)); // 달


		lightTransforms[0].Init(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(1.0f));
		lightTransforms[1].Init(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(1.0f));
		lightTransforms[2].Init(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(1.0f));
		lightTransforms[3].Init(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(1.0f));

		for(int i = 0; i < 10; i++)
		m_shape_manager.GetObject(i)->GetShader()->InputpointLight(lightTransforms, ambient, diffuse, specular);

		m_shape_manager.DrawAll();
	}

private:
	virtual void Draw()
	{
		using QuadCore::BasicObject;
		using QuadCore::Transform;

		BasicObject* Sun_object = new BasicObject("BasicObjects/Sphere", "solarsystem/basicShader_solarsystem", "solarsystem/sun", &SunSphere);
		m_shape_manager.Insert_Object(Sun_object);
		BasicObject* Mercury_object = new BasicObject("BasicObjects/Sphere", "solarsystem/basicShader_solarsystem", "solarsystem/mercury", &MercurySphere);
		m_shape_manager.Insert_Object(Mercury_object);
		BasicObject* Venus_object = new BasicObject("BasicObjects/Sphere", "solarsystem/basicShader_solarsystem", "solarsystem/venus", &VenusSphere);
		m_shape_manager.Insert_Object(Venus_object);
		BasicObject* Earth_object = new BasicObject("BasicObjects/Sphere", "solarsystem/basicShader_solarsystem", "solarsystem/earth", &EarthSphere);
		m_shape_manager.Insert_Object(Earth_object);
		BasicObject* Mars_object = new BasicObject("BasicObjects/Sphere", "solarsystem/basicShader_solarsystem", "solarsystem/mars", &MarsSphere);
		m_shape_manager.Insert_Object(Mars_object);
		BasicObject* Jupiter_object = new BasicObject("BasicObjects/Sphere", "solarsystem/basicShader_solarsystem", "solarsystem/jupiter", &JupiterSphere);
		m_shape_manager.Insert_Object(Jupiter_object);
		BasicObject* Saturn_object = new BasicObject("BasicObjects/Sphere", "solarsystem/basicShader_solarsystem", "solarsystem/saturn", &SaturnSphere);
		m_shape_manager.Insert_Object(Saturn_object);
		BasicObject* Uranus_object = new BasicObject("BasicObjects/Sphere", "solarsystem/basicShader_solarsystem", "solarsystem/uranus", &UranusSphere);
		m_shape_manager.Insert_Object(Uranus_object);
		BasicObject* Neptune_object = new BasicObject("BasicObjects/Sphere", "solarsystem/basicShader_solarsystem", "solarsystem/neptune", &NeptuneSphere);
		m_shape_manager.Insert_Object(Neptune_object);
		BasicObject* Moon_object = new BasicObject("BasicObjects/Sphere", "solarsystem/basicShader_solarsystem", "solarsystem/moon", &MoonSphere);
		m_shape_manager.Insert_Object(Moon_object);
	}

private:
	//mirror
	int subSphereNum = 128;
	float distance = 7.0f; // 행성간 거리 및 크기 비율
	float speed = 0.05f; // 공전주기 속도 비율
	Transform SunSphere; // 태양
	Transform MercurySphere; // 수성
	Transform VenusSphere; // 금성
	Transform EarthSphere; // 지구
	Transform MarsSphere; // 화성
	Transform JupiterSphere; // 목성
	Transform SaturnSphere; // 토성
	Transform UranusSphere; // 천왕성
	Transform NeptuneSphere; // 해왕성

	Transform MoonSphere; // 달
	
	// multiLight
	Transform lightTransforms[4];

	glm::vec3 ambient[4] =
	{
		glm::vec3(0.1f),
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.00f, 0.00f, 0.00f),
	};
	glm::vec3 diffuse[4] =
	{
		glm::vec3(1.0f),
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.00f, 0.00f, 0.00f),
	};
	glm::vec3 specular[4] =
	{
		glm::vec3(1.0f),
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.00f, 0.00f, 0.00f),
	};
};


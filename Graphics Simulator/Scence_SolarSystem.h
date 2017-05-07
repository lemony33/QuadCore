#pragma once

#define LIMIT 128
#include "iScene.h"

using QuadCore::Transform;

class Scence_SolarSystem : public QuadCore::iScene
{
public:

	Scence_SolarSystem()
	{
	}

	virtual ~Scence_SolarSystem()
	{
	}

public:
	virtual void Play(float speed, glm::vec3* pos, glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular)
	{
		if (!m_enable)
			return;
		if (speed < 0.01) this->speed = 0.01f;
		else if (speed > 2.0) this->speed = 2.0f;
		else this->speed = speed;
		printf("rotspeed = %f\n", this->speed);
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

	virtual void Animate()
	{
		// 밑 부분에 각 쉐이더에 빛을 적용하기 위한 for문 최대 갯수 정해주는 변수
		int numberofplanets = 0;

		//행성계
		/////////////////////////////////////////////////////////////////////////////////////
		SunSphere.Init(glm::vec3(0.0f),
			glm::vec3(0.0f),
			glm::vec3(109.0f / 30.0f)); numberofplanets++;// 태양

		/*	부모 좌표(현재 태양 좌표) + { 지구 1.0 기준 태양과의 거리 * 거리 비율값 * 삼각함수( m_counter / 지구 대비 공전 주기 * 속도 비율값) }  */
		MercurySphere.Init(glm::vec3(0.0f + 0.4 * distance * sinf(m_counter / 0.24f * speed),
									0.0f,
									0.0f + 0.4 * distance * cosf(m_counter / 0.24f * speed)),
			glm::vec3(0.0f, m_counter / 59.0f * speed * rotspeed, 0.0f),
			glm::vec3(0.4f)); numberofplanets++;// 수성

		VenusSphere.Init(glm::vec3(0.0f + 0.7 * distance * sinf(m_counter / 0.62f * speed),
									0.0f,
									0.0f + 0.7 * distance * cosf(m_counter / 0.62f * speed)),
			glm::vec3(0.0f, m_counter / 243.0f * speed * rotspeed, 0.0f),
			glm::vec3(0.9f)); numberofplanets++;// 금성

		EarthSphere.Init(glm::vec3(0.0f + 1.0 * distance * sinf(m_counter * 1.0f * speed),
									0.0f,
									0.0f + 1.0 * distance * cosf(m_counter * 1.0f * speed)),
			glm::vec3(0.0f, m_counter / 1.0f * speed * rotspeed, 0.0f),
			glm::vec3(1.0f)); numberofplanets++;// 지구

		MarsSphere.Init(glm::vec3(0.0f + 1.5 * distance * sinf(m_counter / 1.88f * speed),
									0.0f,
									0.0f + 1.5 * distance * cosf(m_counter / 1.88f * speed)),
			glm::vec3(0.0f, m_counter / 1.03f * speed * rotspeed, 0.0f),
			glm::vec3(0.6f)); numberofplanets++;// 화성

		JupiterSphere.Init(glm::vec3(0.0f + 5.2 * distance * sinf(m_counter / 11.86f * speed) / 2.0f,
									0.0f,
									0.0f + 5.2 * distance * cosf(m_counter / 11.86f * speed) / 2.0f),
			glm::vec3(0.0f, m_counter / 0.41f * speed * rotspeed, 0.0f),
			glm::vec3(11.2f / 5.0f)); numberofplanets++;// 목성

		SaturnSphere.Init(glm::vec3(0.0f + 9.5 * distance * sinf(m_counter / 29.46f * speed) / 3.0f,
									0.0f,
									0.0f + 9.5 * distance * cosf(m_counter / 29.46f * speed) / 3.0f),
			glm::vec3(0.0f, m_counter / 0.44f * speed * rotspeed, 0.0f),
			glm::vec3(9.4f / 5.0f)); numberofplanets++;// 토성

		UranusSphere.Init(glm::vec3(0.0f + 19.2 * distance * sinf(m_counter / 84.07f * speed) / 5.0f,
									0.0f,
									0.0f + 19.2 * distance * cosf(m_counter / 84.07f * speed) / 5.0f),
			glm::vec3(0.0f, m_counter / 0.65f * speed * rotspeed, 0.0f),
			glm::vec3(4.0f / 3.0f)); numberofplanets++;// 천왕성

		NeptuneSphere.Init(glm::vec3(0.0f + 30.1 * distance * sinf(m_counter / 164.8f * speed) / 7.0f,
									0.0f,
									0.0f + 30.1 * distance * cosf(m_counter / 164.8f * speed) / 7.0f),
			glm::vec3(0.0f, m_counter / 0.77f * speed * rotspeed, 0.0f),
			glm::vec3(3.9f / 2.0f)); numberofplanets++;// 해왕성

		MoonSphere.Init(glm::vec3(EarthSphere.GetPos().x + 0.7f * distance * sinf(m_counter * 27.0f / 365.0f * speed) / 7.0f,
									0.0f,
									EarthSphere.GetPos().z + 0.7f * distance * cosf(m_counter * 27.0f / 365.0f * speed) / 7.0f),
			glm::vec3(0.0f, m_counter * 27.0f / 365.0f * speed, 0.0f),
			glm::vec3(0.25f)); numberofplanets++;// 달

		SaturnDonutRing.Init(glm::vec3(SaturnSphere.GetPos().x,
			0.0f,
			SaturnSphere.GetPos().z),
			glm::vec3(-0.2f, 0, 0),
			glm::vec3(4.0f, 0.5f, 4.0f)); numberofplanets++;// 토성 띠
		/////////////////////////////////////////////////////////////////////////////////////

		// Scene 내 빛의 위치들
		lightTransforms[0].Init(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(1.0f));
		/*lightTransforms[1].Init(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(1.0f));
		lightTransforms[2].Init(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(1.0f));
		lightTransforms[3].Init(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(1.0f));*/
		
		lightTransforms[4].Init(glm::vec3(0 + nuclear * distance * sinf(m_counter / 0.4f * speed),
			0,
			0 + nuclear * distance * cosf(m_counter / 0.4f * speed)),
			glm::vec3(0, m_counter / 0.5f  * speed, 0),
			glm::vec3(0.3f, 0.2f + 0.1f * sinf(m_counter * speed * 20.0f), 0.3f));
		if (nuclear < 35/7 && reverse == false)
			nuclear += 0.001f;
		else if (nuclear > 35/7 && reverse == false)
			reverse = true;
		else if (nuclear > 0 && reverse == true)
			nuclear -= 0.001f;
		else if (nuclear <= 0 && reverse == true)
			reverse = false;

		//모든 행성 쉐이더에 빛 적용
		for(int i = 0; i < numberofplanets + 5; i++)
		m_shape_manager.GetObject(i)->GetShader()->InputpointLight(lightTransforms, ambient, diffuse, specular);
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

		BasicObject* Saturn_Ring = new BasicObject("BasicObjects/Torus", "solarsystem/basicShader_solarsystem", "solarsystem/saturn_ring", &SaturnDonutRing);
		m_shape_manager.Insert_Object(Saturn_Ring);

		for (int i = 0; i < 5; i++)
		{
			BasicObject* light = new BasicObject("BasicObjects/Sphere", "lamp_texture", "slime", &lightTransforms[i]);
			m_shape_manager.Insert_Object(light);
		}
	}

private:
	bool reverse = false;
	float nuclear = 0;
	float distance = 10.0f; // 행성간 거리 비율
	float speed = 0.1f; // 공전주기 속도 비율
	float rotspeed = 2.0f; // 자전주기 속도 비율
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
	Transform SaturnDonutRing; // 토성 링
	
	// multiLight
	Transform lightTransforms[5];

	glm::vec3 ambient[5] =
	{
		glm::vec3(0.1f), // 태양 빛
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.5f, 0.1f, 0.1f)
	};
	glm::vec3 diffuse[5] =
	{
		glm::vec3(1.0f), // 태양 빛
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.6f, 0.2f, 0.2f)
	};
	glm::vec3 specular[5] =
	{
		glm::vec3(1.0f), // 태양 빛
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.00f, 0.00f, 0.00f),
		glm::vec3(0.6f, 0.2f, 0.2f)
	};
};


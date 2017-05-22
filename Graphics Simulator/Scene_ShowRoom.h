#pragma once

#include "iScene.h"
#include "Render_Mode.h"

#include "ExtraObject.h"
using QuadCore::ExtraObject;


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

		if (IsChanged_RenderMode)
		{
			SetObject(m_object_name, m_sahder_name, m_texture_name);
			IsChanged_RenderMode = false;
		}

		rot += speed*0.01f;
		if (rot > 2.0f*glm::pi<float>())
			rot = 0.0f;


		float radians[3] = {
			g_rotation[0] * glm::pi<float>(),	// / 180.0f
			g_rotation[1] * glm::pi<float>(),
			g_rotation[2] * glm::pi<float>(),
		};


		//printf(" ( %02f , %02f , %02f )", g_rotation[0], g_rotation[1], g_rotation[2]);
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

		m_shape_manager.DrawAll_PolyMode(m_local_coordinate, m_poly_mode);
	}

	

	std::string m_object_name = "";
	std::string m_sahder_name = "";
	std::string m_texture_name = "";


	float m_tess_level_inner;
	float m_tess_level_outer;
	float m_tess_level_scale;
	virtual void Set_TesselMode(float level_inner, float level_outer, float level_scale)
	{
		m_tess_level_inner = level_inner;
		m_tess_level_outer = level_outer;
		m_tess_level_scale = level_scale;
	}


	bool IsChanged_RenderMode = false;
	virtual void Set_RenderMode(int object_mode, int shader_mode, int texture_mode)
	{
		m_object_name = "Final/bunny_zipper";
		switch (object_mode)
		{
		case OBJECT_MODE::Bunny:
			m_object_name = "Final/Bunny";
			IsChanged_RenderMode = true;
			break;
		case OBJECT_MODE::Lucy:
			m_object_name = "Final/HQ_Lucy";
			IsChanged_RenderMode = true;
			break;
		case OBJECT_MODE::Lucycat:
			m_object_name = "Final/lucycat";
			IsChanged_RenderMode = true;
			break;
		case OBJECT_MODE::Lucycat_voronol:
			m_object_name = "Final/lucycat_voronol";
			IsChanged_RenderMode = true;
			break;

		case OBJECT_MODE::bear:
			m_object_name = "Final/bear";
			IsChanged_RenderMode = true;
			break;
		case OBJECT_MODE::nanosuit:
			m_object_name = "Final/nanosuit";
			IsChanged_RenderMode = true;
			break;


			//glove, chair, WineGlasses,
		case OBJECT_MODE::glove:
			m_object_name = "Final/glove";
			IsChanged_RenderMode = true;
			break;
		case OBJECT_MODE::chair:
			m_object_name = "Final/chair";
			IsChanged_RenderMode = true;
			break;
		case OBJECT_MODE::WineGlasses:
			m_object_name = "Final/WineGlasses";
			IsChanged_RenderMode = true;
			break;


			//Torus, Cube, Sphere, Icosphere, CubeHollow,
		case OBJECT_MODE::Torus:
			m_object_name = "BasicObjects/Torus";
			IsChanged_RenderMode = true;
			break;
		case OBJECT_MODE::Cube:
			m_object_name = "BasicObjects/Cube";
			IsChanged_RenderMode = true;
			break;
		case OBJECT_MODE::Sphere:
			m_object_name = "BasicObjects/Sphere";
			IsChanged_RenderMode = true;
			break;
		case OBJECT_MODE::Icosphere:
			m_object_name = "BasicObjects/Icosphere";
			IsChanged_RenderMode = true;
			break;
		case OBJECT_MODE::CubeHollow:
			m_object_name = "BasicObjects/CubeHollow";
			IsChanged_RenderMode = true;
			break;

		default:
			break;
		}

		switch (shader_mode)
		{
		case SHADER_MODE::Phong:
			m_sahder_name = "Final/Fragment_1_Single_Phong";
			IsChanged_RenderMode = true;
			break;
		case SHADER_MODE::Multi:
			m_sahder_name = "Final/Fragment_2_Multi_Phong";
			IsChanged_RenderMode = true;
			break;
		case SHADER_MODE::Rim:
			m_sahder_name = "Final/Fragment_3_Multi-Phong_Rim";
			IsChanged_RenderMode = true;
			break;
		default:
			break;
		}


		switch (texture_mode)
		{
		case TEXTURE_MODE::Bricks:
			m_texture_name = "bricks";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::Skyblue:
			m_texture_name = "skyblue";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::Formula:
			m_texture_name = "formula";
			//m_texture_name = "metal";
			IsChanged_RenderMode = true;
			break;

		case TEXTURE_MODE::dark_spot:
			m_texture_name = "dark_spot";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::diamond:
			m_texture_name = "diamond";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::grain_grass:
			m_texture_name = "grain_grass";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::iron:
			m_texture_name = "iron";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::lines_dark:
			m_texture_name = "lines_dark";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::metal:
			m_texture_name = "metal";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::moon:
			m_texture_name = "moon";
			IsChanged_RenderMode = true;
			break;

		case TEXTURE_MODE::slime:
			m_texture_name = "slime";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::surface_dark:
			m_texture_name = "surface_dark";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::surface_gold_shine:
			m_texture_name = "surface_gold_shine";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::pastel:
			m_texture_name = "pastel";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::wall_brick:
			m_texture_name = "wall_brick";
			IsChanged_RenderMode = true;
			break;
		case TEXTURE_MODE::wood:
			m_texture_name = "wood";
			IsChanged_RenderMode = true;
			break;
		default:
			break;
		}
	}

	float* m_normal_length;
	virtual void Sync_Value_Normal(float* num)
	{
		m_normal_length = num;
		//printf("%.5f\n", *m_normal_length);
	}

	float* m_explode_speed;
	virtual void Sync_Value_Explode_Speed(float* num)
	{
		m_explode_speed = num;
		//printf("%.5f\n", *m_normal_length);
	}

	float* m_explode_factor;
	virtual void Sync_Value_Explode_Factor(float* num)
	{
		m_explode_factor = num;
		//printf("%.5f\n", *m_normal_length);
	}


	float m_effect_counter = 0.0f;
	bool IsEffectStop = false;
	bool IsExplode = false;
	bool IsNormalView = false;
	virtual void Set_EffectMode(int effect_mode, bool flag)
	{
		switch (effect_mode)
		{
		case EFFECT_MODE::EFFECT_PAUSE:
			IsEffectStop = flag;
			break;
		case EFFECT_MODE::EXPLODE:
			IsExplode = flag;
			if (!flag)
				m_effect_counter = 0.0f;
			break;
		case EFFECT_MODE::NORMAL_VIEW:
			IsNormalView = flag;
			break;
		}
	}


public:
	virtual void Animate()
	{
		float r = 3.0f;

		// R, G, B
		//lightTransforms[0].Init(glm::vec3(r*1.0f * sinf(m_counter / 10), 0, r*1.0f * cosf(m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		//lightTransforms[1].Init(glm::vec3(r*1.0f * cos(m_counter / 10), r*1.0f * sinf(m_counter / 10), 0), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		//lightTransforms[2].Init(glm::vec3(0, r*1.0f * cos(m_counter / 10), r*1.0f * sinf(m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));

		// White
		lightTransforms[3].Init(glm::vec3(5.0f * sinf(-m_counter / 10), 0, 5.0f * cosf(-m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));

		lightTransforms[0].Init(Rotate_Axis_normal(glm::vec3(1, 0, 0), m_counter * 5.0f, glm::vec3(0, 0, r)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[1].Init(Rotate_Axis_normal(glm::vec3(0, 1, 0), m_counter * 5.0f, glm::vec3(r, 0, 0)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[2].Init(Rotate_Axis_normal(glm::vec3(0, 0, 1), m_counter * 5.0f, glm::vec3(0, r, 0)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));

		for (int i = 0; i < 5; i++)
			m_shape_manager.GetObject(i)->GetShader()->InputpointLight(lightTransforms, ambient, diffuse, specular);
		
		
		if (IsExplode)
		{
			//printf("%.2f\n", m_effect_counter);
			m_shape_manager.GetObject(0)->GetShader()->SetUniform_explode_factor(m_effect_counter);
		}
		else
		{
			m_shape_manager.GetObject(0)->GetShader()->SetUniform_explode_factor(0.0f, false);
		}

		m_shape_manager.GetObject(0)->GetShader()->Set_Tess_Level_inner(m_tess_level_inner);
		m_shape_manager.GetObject(0)->GetShader()->Set_Tess_Level_outer(m_tess_level_outer);
		m_shape_manager.GetObject(0)->GetShader()->Set_Tess_Level_scale(m_tess_level_scale);

		m_shape_manager.GetObject(0)->GetShader()->Set_NormalViewer(IsNormalView);
		m_shape_manager.GetObject(0)->GetShader()->Set_NormalLength(*m_normal_length);
		m_shape_manager.GetObject(0)->GetShader()->Set_ExplodeSpeed(*m_explode_speed);
		m_shape_manager.GetObject(0)->GetShader()->Set_ExplodeFactor(*m_explode_factor);
		//printf("%.2f\n", *m_explode_speed);

		if(!IsEffectStop)
			m_effect_counter += 0.01f;
	}

	/**********************************************************************************

	[ Quaternion Rotate : 사원수의 회전 ]
	- normal vector(a,b,c)를 축으로 점 p(x,y,z)를 θ˚만큼 회전한다.

	q = { sin(θ/2)n, cos(θ/2) }

	R_q(p) = qpq'¹
	= cosθP + (1-cosθ)(N·P)N + sinθ(N×P)

	· => inner product or dot product
	× => outer product or cross product

	**********************************************************************************/
	inline glm::vec3 Rotate_Axis_normal(glm::vec3 normal, float degree, glm::vec3 point = glm::vec3())
	{
		float radians = degree * glm::pi<float>() / 180.0f;

		float q = cosf(radians) + sinf(radians);

		glm::vec3 mov_pos = (cosf(radians) * point)
			+ ((1 - cosf(radians)) * glm::dot(normal, point) * normal)
			+ (sinf(radians) * glm::cross(normal, point));
		return mov_pos;
	}

private:
	virtual void Draw()
	{
		using QuadCore::BasicObject;
		using QuadCore::Transform;


		// 쉐이더 모드 선택
		Set_RenderMode(OBJECT_MODE::Bunny, SHADER_MODE::Phong, TEXTURE_MODE::Bricks);
		SetObject(m_object_name, m_sahder_name, m_texture_name);


		m_shape_manager.Insert_Object(object);

		for (int i = 0; i < 4; i++)
		{
			BasicObject* light = new BasicObject("test/octahedron", "lamp", "moon", &lightTransforms[i]);
			m_shape_manager.Insert_Object(light);
		}
	}

	//
	//
	//
	void SetObject(std::string mesh, std::string shader, std::string texture)
	{
		using QuadCore::ExtraObject;
		using QuadCore::Transform;

		if ((transform_obj == NULL) && (object == NULL))
		{
			transform_obj = new Transform(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(1.0f));

			object = new ExtraObject(mesh, shader, texture, transform_obj, IsNormalView);
			IsChanged_RenderMode = false;
						
		}
		else
		{
			transform_obj = new Transform(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(1.0f));
			object = new ExtraObject(mesh, shader, texture, transform_obj, IsNormalView);
			m_shape_manager.Modify_Objet(0, object);

		}
	}

private:
	Transform* transform_obj;
	ExtraObject* object;

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

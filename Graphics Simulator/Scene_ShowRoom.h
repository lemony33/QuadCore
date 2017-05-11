#pragma once

#include "iScene.h"
#include "Render_Mode.h"


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

		m_shape_manager.DrawAll(m_local_coordinate);
	}



	//virtual void Set_RenderMode(OBJECT_MODE object_mode, SHADER_MODE shader_mode, TEXTURE_MODE texture_mode)
	//{

	//}

	//virtual void Set_RenderMode(SceneManager::OBJECT_MODE object_mode, SceneManager::SHADER_MODE shader_mode, SceneManager::TEXTURE_MODE texture_mode)
	//{
	//}

	std::string m_object_name = "";
	std::string m_sahder_name = "";
	std::string m_texture_name = "";

	bool IsChanged_RenderMode = false;
	virtual void Set_RenderMode(int object_mode, int shader_mode, int texture_mode)
	{
		switch (object_mode)
		{
		case OBJECT_MODE::Bunny:
			m_object_name = "Bunny";
			IsChanged_RenderMode = true;
			break;
		case OBJECT_MODE::Lucy:
			m_object_name = "Lucy";
			IsChanged_RenderMode = true;
			break;
		case OBJECT_MODE::Lucycat:
			m_object_name = "Voronoi_Lucy";
			IsChanged_RenderMode = true;
			break;
		default:
			break;
		}

		switch (shader_mode)
		{
		case SHADER_MODE::Phong:
			m_sahder_name = "basicShader_light_edit";
			IsChanged_RenderMode = true;
			break;
		case SHADER_MODE::Multi:
			m_sahder_name = "basicShader_multilight_prev";
			IsChanged_RenderMode = true;
			break;
		case SHADER_MODE::Rim:
			m_sahder_name = "../multi-PhongRim_ver1.3";
			IsChanged_RenderMode = true;
			break;
		default:
			break;
		}
		//object = new BasicObject("Voronoi_Lucy", "basicShader_light_edit", "skyblue", transform_obj);
		//object = new BasicObject("Voronoi_Lucy", "basicShader_multilight_prev", "skyblue", transform_obj);
		//object = new BasicObject("Voronoi_Lucy", "../multi-PhongRim_ver1.3", "skyblue", transform_obj);

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
			IsChanged_RenderMode = true;
			break;
		default:
			break;
		}
	}


public:
	virtual void Animate()
	{
		/*lightTransforms[0].Init(glm::vec3(100.0f));
		lightTransforms[1].Init(glm::vec3(100.0f));
		lightTransforms[2].Init(glm::vec3(100.0f));*/

		lightTransforms[0].Init(glm::vec3(1.0f * sinf(m_counter / 10), 0, 1.0f * cosf(m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		///lightTransforms[1].Init(glm::vec3(1.0f * cos(m_counter / 10), 1.0f * sinf(m_counter / 10), 0), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		///lightTransforms[2].Init(glm::vec3(0, 1.0f * cos(m_counter / 10), 1.0f * sinf(m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		///lightTransforms[3].Init(glm::vec3(5.0f * sinf(-m_counter / 10), 0, 5.0f * cosf(-m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		
		float r = 3.0f;
		lightTransforms[1].Init(glm::vec3(r*1.0f * cos(m_counter / 10), r*1.0f * sinf(m_counter / 10), 0), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[2].Init(glm::vec3(0, r*1.0f * cos(m_counter / 10), r*1.0f * sinf(m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));
		lightTransforms[3].Init(glm::vec3(r*5.0f * sinf(-m_counter / 10), 0, r*5.0f * cosf(-m_counter / 10)), glm::vec3(), glm::vec3(0.1f, 0.1f, 0.1f));

		//lightTransforms[2].Init(Rotate_Axis_normal(glm::vec3(1, 0, 0), sinf(m_counter)*360.0f), glm::vec3(0, 0, r));
		//lightTransforms[2].Init(Rotate_Axis_normal(glm::vec3(0, 1, 0), sinf(m_counter)*360.0f), glm::vec3(0, 0, r));
		//lightTransforms[3].Init(Rotate_Axis_normal(glm::vec3(0, 0, 1), sinf(m_counter)*360.0f), glm::vec3(0, r, 0));

		for (int i = 0; i < 5; i++)
			m_shape_manager.GetObject(i)->GetShader()->InputpointLight(lightTransforms, ambient, diffuse, specular);
	}

	/**********************************************************************************

	[ Quaternion Rotate : ������� ȸ�� ]
	- normal vector(a,b,c)�� ������ �� p(x,y,z)�� �袪��ŭ ȸ���Ѵ�.

	q = { sin(��/2)n, cos(��/2) }

	R_q(p) = qpq'��
	= cos��P + (1-cos��)(N��P)N + sin��(N��P)

	�� => inner product or dot product
	�� => outer product or cross product

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

		//// multiLight		
		//multitest = new Transform(glm::vec3(0, 0.0f, 0), glm::vec3(), glm::vec3(1.0f));
		//object = new BasicObject("Voronoi_Lucy", "basicShader_multilight_prev", "bricks", multitest);

		//multitest = new Transform(glm::vec3(0, -1.0f, 0), glm::vec3(), glm::vec3(50.0f));
		//object = new BasicObject("test/half_lucy", "basicShader_multilight_prev", "bricks", multitest);

		//multitest = new Transform(glm::vec3(0, -2.0f, 0), glm::vec3(), glm::vec3(20.0f));
		//object = new BasicObject("bunny", "basicShader_multilight_prev", "bricks", multitest);
		
		///transform_obj = new Transform(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(20.0f));
		//////transform_obj = new Transform(glm::vec3(0, -2.0f, 0), glm::vec3(), glm::vec3(20.0f));
		////object = new BasicObject("bunny", "multi-PhongRim", "skyblue", transform_obj);
		//object = new BasicObject("bunny", "../multi-PhongRim_ver1.3", "skyblue", transform_obj);
		///object = new BasicObject("bunny", "multi-PhongRim", "skyblue", transform_obj);
		//object = new BasicObject("bunny", "multi-basicShader_multilight_prev", "skyblue", transform_obj);


		//transform_obj = new Transform(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(1.0f));
		//object = new BasicObject("BasicObjects/Cube", "multi-PhongRim", "skyblue", transform_obj);

		// ���̴� ��� ����
		Set_RenderMode(OBJECT_MODE::Bunny, SHADER_MODE::Phong, TEXTURE_MODE::Bricks);
		SetObject(m_object_name, m_sahder_name, m_texture_name);

		//SetObject("bunny", "../multi-PhongRim_ver1.3", "skyblue");

		////////////////////////////////
		// ���̴� �����ۼ��� �׽�Ʈ �ڵ�
		///transform_obj = new Transform(glm::vec3(0, -2.0f, 0), glm::vec3(), glm::vec3(20.0f));	//0510
		//object = new BasicObject("bunny", "basicShader_light_edit", "skyblue", transform_obj);
		///object = new BasicObject("bunny", "basicShader_multilight_prev", "bricks", transform_obj);	//0510
		//object = new BasicObject("bunny", "../multi-PhongRim_ver1.3", "skyblue", transform_obj);

		//transform_obj = new Transform(glm::vec3(0, -2.0f, 0), glm::vec3(), glm::vec3(50.0f));
		//object = new BasicObject("test/half_lucy", "basicShader_light_edit", "skyblue", transform_obj);
		//object = new BasicObject("test/half_lucy", "basicShader_multilight_prev", "bricks", transform_obj);
		//object = new BasicObject("test/half_lucy", "../multi-PhongRim_ver1.3", "skyblue", transform_obj);

		//transform_obj = new Transform(glm::vec3(0, 0, 0), glm::vec3(), glm::vec3(0.5f));
		//object = new BasicObject("Voronoi_Lucy", "basicShader_light_edit", "skyblue", transform_obj);
		//object = new BasicObject("Voronoi_Lucy", "basicShader_multilight_prev", "skyblue", transform_obj);
		//object = new BasicObject("Voronoi_Lucy", "../multi-PhongRim_ver1.3", "skyblue", transform_obj);

		//basicShader_light_edit
		//basicShader_multilight_prev
		//../multi-PhongRim_ver1.3

		m_shape_manager.Insert_Object(object);

		for (int i = 0; i < 4; i++)
		{
			BasicObject* light = new BasicObject("test/octahedron", "lamp_prev", "moon", &lightTransforms[i]);
			m_shape_manager.Insert_Object(light);
		}
	}

	//
	//
	//
	void SetObject(std::string mesh, std::string shader, std::string texture)
	{
		using QuadCore::BasicObject;
		using QuadCore::Transform;

		if ((transform_obj == NULL) && (object == NULL))
		{
			transform_obj = new Transform(glm::vec3(0, -2.0f, 0), glm::vec3(), glm::vec3(20.0f));
			object = new BasicObject(mesh, shader, texture, transform_obj);
			IsChanged_RenderMode = false;
						
		}
		else
		{
/*			transform_obj = NULL;
			object = NULL;		*/			

			//transform_obj->Init(glm::vec3(2.0f, -2.0f, 0), glm::vec3(), glm::vec3(20.0f));
			///object->Init(mesh, shader, texture, transform_obj);

			///QuadCore::BasicObject* pObject = new BasicObject(mesh, shader, texture, transform_obj);
			transform_obj = new Transform(glm::vec3(), glm::vec3(), glm::vec3(20.0f));
			object = new BasicObject(mesh, shader, texture, transform_obj);
			m_shape_manager.Modify_Objet(0, object);

			//object = new BasicObject(mesh, shader, texture, transform_obj);
			//m_shape_manager.Insert_Object(object);

			//m_shape_manager.Modify_Objet(0, object);


			//// �ٸ� �����Ϳ� ���� ������Ʈ�� ����
			//QuadCore::Transform*   pTransform = transform_obj;
			//QuadCore::BasicObject* pObject = object;

			//// ���� �����Ϳ� ���ο� ������Ʈ �Ҵ�
			//transform_obj = new Transform(glm::vec3(), glm::vec3(), glm::vec3(20.0f));
			//object = new BasicObject(mesh, shader, texture, transform_obj);

			//// �ٸ� �����Ϳ� ����� ���� ������Ʈ ����
			//delete(pTransform);
			//delete(pObject);
			//pTransform = NULL;
			//pObject = NULL;
		}

		//transform_obj = NULL;
		//object = NULL;

		//delete(transform_obj);
		//delete(object);
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

	//float speed = 0.1f; // �����ֱ� �ӵ� ����
	float rot = 0.0f;

	float prev_rot[3] = {};
	//float curr_rot[3] = {};
};

#pragma once

#include "ShapeManager.h"
#include "iScene.h"

#include "World_coordinate.h"
#include "miniUI_coordinate.h"

#include "DrawMap.h"

#include "Scene_main.h"

// �ó�����
#include "Scence_mirror.h"			// 1.SkyBox
#include "Scence_SolarSystem.h"		// 2.Solar System
#include "Scene_ShowRoom.h"			// 3.Show Room

#include "Scence_moving_wall.h"
#include "Scence_moving_block.h"
#include "Scence_moving_cube.h"
#include "Scence_reflect_shader.h"	// temp
#include "Scence_multi_light.h"
#include "Scene_basicObjects.h"

#include "Scene_SkyBox_Universe.h"
#include "Scene_SkyBox.h"

#include "Scene_room.h"

//#include "UI_TwBar.h"
//#include "Render_Mode.h"
#include "Menu.h"




class SceneManager
{
public:
	Menu menu;
	
	SceneManager()
	{
		menu.Init(true);
	}

	virtual ~SceneManager()
	{
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// �ʿ��� ������ �ʱ�ȭ
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Init(QuadCore::Camera* camera, QuadCore::Display* display)
	{
		m_camera = camera;
		m_display = display;

		m_background_list.push_back(new Scene_main);
		m_background_list.push_back(new Scene_SkyBox);
		m_background_list.push_back(new Scene_SkyBox_Universe);
		m_background_list.push_back(new Scene_room);

		for (int i = 0; i < m_background_list.size(); i++)
		{
			m_background_list.at(i)->SetEnable(true);
		}

		
		m_scene_list.push_back(new Scene_main);
		//m_scene_list.push_back(new Scene_main);
		//m_scene_list.push_back(new Scene_main);
		m_scene_list.push_back(new Scence_mirror);			// 1.SkyBox
		m_scene_list.push_back(new Scence_SolarSystem);		// 2.Solar System
		m_scene_list.push_back(new Scene_ShowRoom);			// 3.Show Room
		m_scene_list.push_back(new Scence_moving_wall);		// ���� ��ġ ������ �� ���
		//m_scene_list.push_back(new Scence_moving_block);	// ȸ���� ������� ������Ʈ ��ġ�غ��� ������
		m_scene_list.push_back(new Scene_basicObjects);		// �پ��� ������Ʈ���� ���� ����Ǵ� ��� �ÿ�
		//m_scene_list.push_back(new Scence_multi_light);		// �������� ��ü�� ����Ǵ� ��
		m_scene_list.push_back(new Scene_main);
		m_scene_list.push_back(new Scene_main);
		m_scene_list.push_back(new Scene_main);
		m_scene_list.push_back(new Scene_main);
		///m_scene_list.push_back(new Scence_reflect_shader);	// �̻�� �׽�Ʈ ����
				
		for (int i = 0; i < m_scene_list.size(); i++)
		{
			m_scene_list.at(i)->SetEnable(true);
		}

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

		dMap.Init(camera);
		dMap.SetProperty(100, 1.0f, glm::vec4(0.7f, 0.7f, 0.7f, 3.0f));		// Draw Map

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		for (int i = 0; i < m_background_list.size(); i++)
		{
			m_background_list.at(i)->Init(camera);
		}
		for (int i = 0; i < m_scene_list.size(); i++)
		{
			m_scene_list.at(i)->Init(camera);
		}
	}

public:

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// �̸� ������ �ó������� �����Ѵ�.
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Select_Scene()
	{
		//// �� �ߺ����� �ȵǵ��� ó���� ��
		switch (menu.BackgroundNum_prev)
		{
		case 1:
			if (menu.m_scene_1 == true && menu.m_scene_2 == true)
			{
				menu.m_scene_1 = false;
				menu.BackgroundNum = 2;
			}
			if (menu.m_scene_3 == true && menu.m_scene_1 == true)
			{
				menu.m_scene_1 = false;
				menu.BackgroundNum = 3;
			}
			break;
		case 2:
			if (menu.m_scene_1 == true && menu.m_scene_2 == true)
			{
				menu.m_scene_2 = false;
				menu.BackgroundNum = 1;
			}
			if (menu.m_scene_2 == true && menu.m_scene_3 == true)
			{
				menu.m_scene_2 = false;
				menu.BackgroundNum = 3;
			}
			break;
		case 3:
			if (menu.m_scene_2 == true && menu.m_scene_3 == true)
			{
				menu.m_scene_3 = false;
				menu.BackgroundNum = 2;
			}
			if (menu.m_scene_3 == true && menu.m_scene_1 == true)
			{
				menu.m_scene_3 = false;
				menu.BackgroundNum = 1;
			}
			break;
		}

		// �� ����â
		if (menu.m_scene_1) {
			menu.BackgroundNum_prev = 1;
			menu.BackgroundNum = 1;

			menu.SceneNumber = 1;	// ���ϴ� ������ ����
		}
		if (menu.m_scene_2) {
			menu.BackgroundNum_prev = 2;
			menu.BackgroundNum = 2;

			menu.SceneNumber = 2;	// ���ϴ� ������ ����
		}
		if (menu.m_scene_3) {
			menu.BackgroundNum_prev = 3;
			menu.BackgroundNum = 3;

			menu.SceneNumber = 3;	// ���ϴ� ������ ����
		}

		if (menu.IsDefault)
		{
			menu.m_scene_1 = false;
			menu.m_scene_2 = false;
			menu.m_scene_3 = false;

			menu.BackgroundNum = 0;
			menu.SceneNumber = 0;
		}
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// ����� ����Ѵ�.
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Play()
	{
		if(!menu.m_stopper)
			menu.counter += 0.05f * menu.counter_speed;

		if (menu.m_counter_reset)
		{
			menu.counter_speed = 1.0f;
			menu.counter = 0.0f;
			menu.m_counter_reset = false;
		}

		QuadCore::iScene::SetCounter(menu.counter);

		m_display->Clear(menu.m_bgColor[0], menu.m_bgColor[1], menu.m_bgColor[2], 1.0f);

		this->Select_Scene();

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		
		if (menu.switch_grid_map)
		{
			dMap.DrawPlane();		// Draw Map	
		}
				

		//scence_mirror->KeyInput(m_cur_key);		

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		for (int i = 0; i < m_background_list.size(); i++)
		{
			if (i == menu.BackgroundNum)
			{				
				m_background_list.at(i)->Play();
			}
		}


		for (int i = 0; i < m_scene_list.size(); i++)
		{
			glm::vec3 pos[3]; 
			glm::vec3 ambient[3];
			glm::vec3 diffuse[3];
			glm::vec3 specular[3];
			for(int i = 0; i < 3; i++)
			{
				pos[i] = glm::vec3(menu.multilights[i].posX, menu.multilights[i].posY, menu.multilights[i].posZ);
				ambient[i] = glm::vec3(menu.multilights[i].ambient[0], menu.multilights[i].ambient[1], menu.multilights[i].ambient[2]);
				diffuse[i] = glm::vec3(menu.multilights[i].diffuse[0], menu.multilights[i].diffuse[1], menu.multilights[i].diffuse[2]);
				specular[i] = glm::vec3(menu.multilights[i].specular[0], menu.multilights[i].specular[1], menu.multilights[i].specular[2]);
			}

			//
			float final_speed = 0;
			
			//UI ���� �´� ���� �÷���
			if (i == menu.SceneNumber)
			{
				int j = i;

				m_scene_list.at(j)->Set_LocalCoordinate(menu.switch_local_coordinate);

				switch (i)
				{
				case 0:								// 0.Default(none)
					menu.TurnOffMirrorUI();
					menu.TurnOffSolarUI();
					menu.TurnOffRoomUI();
					m_scene_list.at(j)->Set_PolyMode(menu.m_wireframe);
					m_scene_list.at(j)->Play();
					break;
				case 1:								// 1.SkyBox
					menu.TurnOnMirrorUI();
					menu.TurnOffSolarUI();
					menu.TurnOffRoomUI();
					m_scene_list.at(j)->Set_PolyMode(menu.m_wireframe);
					m_scene_list.at(j)->Play(menu.Spheres);
					break;
				case 2:								// 2.Solar System
					//m_scene_list.at(j)->Play();
					menu.TurnOffMirrorUI();
					menu.TurnOnSolarUI();
					menu.TurnOffRoomUI();
					m_scene_list.at(j)->Set_PolyMode(menu.m_wireframe);
					m_scene_list.at(j)->Play(menu.rotspeed, pos, ambient, diffuse, specular);
					break;
				case 3:								// 3.Show Room
					menu.TurnOffMirrorUI();
					menu.TurnOffSolarUI();
					menu.TurnOnRoomUI();
					//m_scene_list.at(j)->Play();
					final_speed = menu.rotspeed_object;

					if (menu.Rotation == Menu::ROT_OFF)
						final_speed = 0;
					else if (menu.Rotation == Menu::ROT_CW)
						final_speed = -menu.rotspeed_object;
					else if (menu.Rotation == Menu::ROT_CCW)
						final_speed = +menu.rotspeed_object;


					if (menu.m_stopper)
						final_speed = 0;

					if (menu.reset_rotation)
					{
						menu.g_Rotation[0] = 0.0f;
						menu.g_Rotation[1] = 0.0f;
						menu.g_Rotation[2] = 0.0f;
						menu.reset_rotation = false;
					}

					if(menu.IsChanged_Reder_Mode())
						m_scene_list.at(j)->Set_RenderMode(menu.object_mode, menu.shader_mode, menu.texture_mode);


					m_scene_list.at(j)->Set_EffectMode(EFFECT_MODE::EFFECT_PAUSE, menu.is_effect_pause);
					m_scene_list.at(j)->Set_EffectMode(EFFECT_MODE::EXPLODE, menu.is_explode);
					m_scene_list.at(j)->Set_EffectMode(EFFECT_MODE::NORMAL_VIEW, menu.is_normal_view);

					m_scene_list.at(j)->Sync_Value_Explode_Speed(&menu.m_explode_speed);
					m_scene_list.at(j)->Sync_Value_Normal(&menu.m_normal_length);

					m_scene_list.at(j)->Sync_Value_Explode_Factor(&menu.m_explode_factor);

					
					// Normal Viewer ������ ����� ��ε�
					if (menu.IsChanged_Effect_Mode())
					{
						//m_normal_length = 0.2f;
						m_scene_list.at(j)->Set_RenderMode(menu.object_mode, menu.shader_mode, menu.texture_mode);
					}

					m_scene_list.at(j)->Set_PolyMode(menu.m_poly_mode);
					m_scene_list.at(j)->Play(menu.g_Rotation, final_speed, pos, ambient, diffuse, specular);
					break;
				default:
					menu.TurnOffMirrorUI();
					menu.TurnOffSolarUI();
					menu.TurnOffRoomUI();
					m_scene_list.at(j)->Play();
					break;
				}
			}
		}

		menu.SetTime(glfwGetTime());

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		// Draw tweak bar UI
		TwDraw();


		//////////////////////////////////////////////////////////////////////
		////// UI ��ǥ�� �׸���
		m_world_coordinate.Draw(m_camera, menu.switch_world_coordinate);
		m_mini_coordinate.Draw(m_camera, menu.switch_mini_coordinate);
		//////////////////////////////////////////////////////////////////////
	}
	
private:

	std::vector<QuadCore::iScene*> m_background_list;
	std::vector<QuadCore::iScene*> m_scene_list;

	QuadCore::DrawMap dMap;

	QuadCore::Camera* m_camera;
	QuadCore::Display* m_display;

	QuadCore::miniUI_coordinate m_mini_coordinate;
	QuadCore::World_coordinate m_world_coordinate;
};


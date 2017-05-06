#pragma once

#include "ShapeManager.h"
#include "iScene.h"

#include "DrawMap.h"

#include "Scene_main.h"
#include "Scence_moving_wall.h"
#include "Scence_moving_block.h"
#include "Scence_moving_cube.h"
#include "Scence_reflect_shader.h"
#include "Scence_multi_light.h"
#include "Scene_basicObjects.h"
//#include "Scence_mirror.h"
#include "Scence_SolarSystem.h"
#include "Scene_SkyBox_Universe.h"
#include "Scene_SkyBox.h"

#include "Scene_room.h"

#include "UI_TwBar.h"

class SceneManager
{
public:

	float bgColor[3] = { 0.1f, 0.2f, 0.4f };         // Background color 
	unsigned char cubeColor[4] = { 255, 0, 0, 128 }; // Model color (32bits RGBA)
	float g_Rotation[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float g_LightDirection[3] = { -0.57735f, -0.57735f, -0.57735f };

	Scene scene;
	TwBar *mainUI; // play �Լ����� UI �ҷ������� �ϱ����� �߰�. 
	SceneManager()
	{		
		

		// Initialize AntTweakBar
		TwInit(TW_OPENGL, NULL);

		// UI_Bar �̸� // Create a tweak bar
		TwBar *mainBar = TwNewBar("Main");
		TwDefine(" Main label='MAIN' position='30 30' alpha=0 help='Use this bar to edit the main in the scene.' ");

		// �ð�
		TwAddVarRO(mainBar, "Time", TW_TYPE_DOUBLE, &scene.time, "precision=1 help='Time (in seconds).' ");

		TwAddSeparator(mainBar, "", NULL);	// �Ʒ��ʿ� line����
		
		// ��� �����ϴ� �޴�, SceneNumber ������ ������
		TwAddVarRW(mainBar, "Background Number", TW_TYPE_INT32, &scene.BackgroundNum,
			" min=0 max=3 help='Change Background' ");

		// �� �����ϴ� �޴�, SceneNumber ������ ������
		TwAddVarRW(mainBar, "Scene Number", TW_TYPE_INT32, &scene.SceneNumber,
			" min=0 max=3 help='Change Scene' ");
		//TwAddVarRW(TwBar *bar, const char *name, TwType type, void *var, const char *def);
		TwAddSeparator(mainBar, "", NULL);

		///TwAddButton(mainBar, "Button", TW_TYPE_CDSTRING, , );
		
		/*
		// Wireframe ȿ��
		TwAddVarRW(mainBar, "Wireframe", TW_TYPE_BOOLCPP, &scene.Wireframe,
			"key=w help='Toggle wireframe display mode.' ");

		TwAddSeparator(mainBar, "", NULL);
		
		// Background �÷� ����
		TwAddVarRW(mainBar, "Background Color", TW_TYPE_COLOR3F, &scene.BgColor0,
			" help='Change the top background color.' ");

		TwAddSeparator(mainBar, "", NULL);

		// Cube �÷� ����
		TwAddVarRW(mainBar, "Obj Color", TW_TYPE_COLOR32, &cubeColor,
			"alpha help='Color and transparency of the cube.' ");

		TwAddSeparator(mainBar, "", NULL);

		// ���� Rotation Speed ���� // Its key shortcuts are [s] and [S].
		TwAddVarRW(mainBar, "Obj Rotation Speed", TW_TYPE_DOUBLE, &scene.speed,
			" min=0 max=10 step=0.01 keyIncr=s keyDecr=S help='Rotation speed (turns/second)' ");

		TwAddSeparator(mainBar, "", NULL);

		// ���� Rotation 
		TwAddVarRW(mainBar, "Obj Rotation", TW_TYPE_QUAT4F, &g_Rotation,
			" opened=true help='Change the object orientation.' ");

		TwAddSeparator(mainBar, "", NULL);

		// ���� Rotation ���
		TwEnumVal rotationEV[] = { { Scene::ROT_OFF, "Stopped" },
		{ Scene::ROT_CW,  "Clockwise" },
		{ Scene::ROT_CCW, "Counter-clockwise" } };
		TwType rotationType = TwDefineEnum("Rotation Mode", rotationEV, 3);
		TwAddVarRW(mainBar, "Obj Rotation Scene", rotationType, &scene.Rotation,
			" keyIncr=Backspace keyDecr=SHIFT+Backspace help='Stop or change the rotation mode.' ");
		*/


		scene.Init(true);

		mainUI = mainBar; // �� �Լ����� ���ǵ� UI�� ������ ����
		
	}

	virtual ~SceneManager()
	{
	}

	//Scence_mirror* scence_mirror = new Scence_mirror();

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// �ʿ��� ������ �ʱ�ȭ
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Init(QuadCore::Camera* camera)
	{
		m_background_list.push_back(new Scene_main);
		m_background_list.push_back(new Scene_SkyBox);
		m_background_list.push_back(new Scene_SkyBox_Universe);
		m_background_list.push_back(new Scene_room);

		m_background_list.at(1)->SetEnable(true);
		m_background_list.at(2)->SetEnable(true);
		m_background_list.at(3)->SetEnable(true);

		
		m_scene_list.push_back(new Scene_main);
		m_scene_list.push_back(new Scene_basicObjects);
		m_scene_list.push_back(new Scence_moving_wall);
		m_scene_list.push_back(new Scence_moving_block);
		m_scene_list.push_back(new Scene_main);
		m_scene_list.push_back(new Scene_main);
		m_scene_list.push_back(new Scene_main);
		m_scene_list.push_back(new Scene_main);

		////m_scene_list.push_back(new Scene_main);
		////m_scene_list.push_back(new Scene_basicObjects);
		////m_scene_list.push_back(new Scence_moving_wall);
		////m_scene_list.push_back(new Scence_moving_block);
		//m_scene_list.push_back(new Scence_multi_light);
		//m_scene_list.push_back(new Scence_reflect_shader);		
		//m_scene_list.push_back(new Scence_SolarSystem); 
		////m_scene_list.push_back(new Scence_mirror); // �ε� �� ��û ��
		//m_scene_list.push_back(scence_mirror); // �ε� �� ��û ��

		

		m_scene_list.at(0)->SetEnable(true);	//Scene_SkyBox
		m_scene_list.at(1)->SetEnable(true);	//Scene_main
		m_scene_list.at(2)->SetEnable(true);	//Scene_basicObjects
		m_scene_list.at(3)->SetEnable(true);	//Scence_moving_wall
		m_scene_list.at(4)->SetEnable(true);	//Scence_moving_block
		m_scene_list.at(5)->SetEnable(true);	//Scence_moving_cube
		//m_scene_list.at(6)->SetEnable(false);	//Scence_reflect_shader
		//m_scene_list.at(7)->SetEnable(false);	//Scence_multi_light
		//m_scene_list.at(8)->SetEnable(true);	//Scence_SolarSystem
		//m_scene_list.at(9)->SetEnable(false);	//Scence_mirror

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
		char m_cur_key = NULL;
		void Set_CurKey(char cur_key)
		{
			m_cur_key = cur_key;
		}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// ����� ����Ѵ�.
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Play()
	{		
		counter += 0.05f;
		QuadCore::iScene::SetCounter(counter);

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

		//dMap.DrawPlane();		// Draw Map	

		
		//scence_mirror->KeyInput(m_cur_key);

		
		// TwSimple ����߰�
		//display.Clear(scene.BgColor0[0], scene.BgColor0[1], scene.BgColor0[2], 1);	// ��� �ʱ�ȭ	
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		for (int i = 0; i < m_background_list.size(); i++)
		{
			if (i == scene.BackgroundNum)
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
				pos[i] = glm::vec3(scene.multilights[i].posX, scene.multilights[i].posY, scene.multilights[i].posZ);
				ambient[i] = glm::vec3(scene.multilights[i].ambient[0], scene.multilights[i].ambient[1], scene.multilights[i].ambient[2]);
				diffuse[i] = glm::vec3(scene.multilights[i].diffuse[0], scene.multilights[i].diffuse[1], scene.multilights[i].diffuse[2]);
				specular[i] = glm::vec3(scene.multilights[i].specular[0], scene.multilights[i].specular[1], scene.multilights[i].specular[2]);
			}

			//
			

			//UI ���� �´� ���� �÷���
			if (i == scene.SceneNumber)
			{
				int j = i;
				switch (i)
				{
				case 0:
					m_scene_list.at(j)->Play();
					break;
				case 1:
					m_scene_list.at(j)->Play();
					break;
				case 2:
					m_scene_list.at(j)->Play();
					break;
				case 3:
					m_scene_list.at(j)->Play();
					break;
				}
			}
			/*
			//UI ���� �´� ���� �÷���
			if (i == scene.SceneNumber)
			{
				int j = i + 3;
				switch (i)
				{
				case 0:
					//�� ���
					//m_scene_list.at(1)->Play();
					m_scene_list.at(j)->Play();
					//sphere �޴� ����. ������ ���ٰ� �ֿܼ� �޽����� �߳� �������
					TwRemoveVar(mainUI, "NumberofSphere");
					break;

				case 1:
					//�� ���
					m_scene_list.at(0)->Play();
					m_scene_list.at(j)->Play();
					//sphere �޴� ����. ������ ���ٰ� �ֿܼ� �޽����� �߳� �������
					TwRemoveVar(mainUI, "NumberofSphere");
					break;

				case 2:
					//�� ���
					m_scene_list.at(1)->Play();
					m_scene_list.at(j)->Play(pos, ambient, diffuse, specular);
					
					//sphere �޴� ����. ������ ���ٰ� �ֿܼ� �޽����� �߳� �������
					TwRemoveVar(mainUI, "NumberofSphere");
					break;

				case 3:
					//sphere ���� ���ϴ� UI �߰�. �ֿܼ��� �������� ǥ�����ָ� �ߺ� ���� �ȵǰ� ������
					TwAddVarRW(mainUI, "NumberofSphere", TW_TYPE_INT32, &scene.Spheres,
						" min=0 max=64 help='Change a number of sphere' ");
					//�� ���
					m_scene_list.at(0)->Play();
					m_scene_list.at(3)->Play();
					m_scene_list.at(j)->Play(scene.Spheres);
					break;

				default:
					break;
				}				
			}
			*/
		}

		// Rotate model	// TwSimple Rotation �߰�
		scene.dt = glfwGetTime() - scene.time;
		if (scene.dt < 0) scene.dt = 0;
		scene.time += scene.dt;
		scene.turn += scene.speed*scene.dt;

		///
		// Move lights
		scene.Update(scene.time);

		// Draw Light UI 
		scene.Draw();

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		// Draw tweak bar UI
		TwDraw();
	}
	
private:
	float counter = 0.0f;

	std::vector<QuadCore::iScene*> m_background_list;
	std::vector<QuadCore::iScene*> m_scene_list;

	QuadCore::DrawMap dMap;
};


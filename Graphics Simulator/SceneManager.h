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
#include "Scence_mirror.h"
#include "Scence_SolarSystem.h"

#include "Scene_SkyBox.h"


#include "UI_TwBar.h"

class SceneManager
{
public:

	float bgColor[3] = { 0.1f, 0.2f, 0.4f };         // Background color 
	unsigned char cubeColor[4] = { 255, 0, 0, 128 }; // Model color (32bits RGBA)
	float g_Rotation[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float g_LightDirection[3] = { -0.57735f, -0.57735f, -0.57735f };

	Scene scene;

	SceneManager()
	{		
		

		// Initialize AntTweakBar
		TwInit(TW_OPENGL, NULL);

		// UI_Bar 이름 // Create a tweak bar
		TwBar *mainBar = TwNewBar("Main");
		TwDefine(" Main label='MAIN' position='30 30' alpha=0 help='Use this bar to edit the main in the scene.' ");

		// 시간
		TwAddVarRO(mainBar, "Time", TW_TYPE_DOUBLE, &scene.time, "precision=1 help='Time (in seconds).' ");

		TwAddSeparator(mainBar, "", NULL);	// 아래쪽에 line생성

											// Wireframe 효과
		TwAddVarRW(mainBar, "Wireframe", TW_TYPE_BOOLCPP, &scene.Wireframe,
			"key=w help='Toggle wireframe display mode.' ");

		TwAddSeparator(mainBar, "", NULL);

		// Background 컬러 변경
		TwAddVarRW(mainBar, "Background Color", TW_TYPE_COLOR3F, &scene.BgColor0,
			" help='Change the top background color.' ");

		TwAddSeparator(mainBar, "", NULL);

		// Cube 컬러 변경
		TwAddVarRW(mainBar, "Obj Color", TW_TYPE_COLOR32, &cubeColor,
			"alpha help='Color and transparency of the cube.' ");

		TwAddSeparator(mainBar, "", NULL);

		// 도형 Rotation Speed 조정 // Its key shortcuts are [s] and [S].
		TwAddVarRW(mainBar, "Obj Rotation Speed", TW_TYPE_DOUBLE, &scene.speed,
			" min=0 max=10 step=0.01 keyIncr=s keyDecr=S help='Rotation speed (turns/second)' ");

		TwAddSeparator(mainBar, "", NULL);

		// 도형 Rotation 
		TwAddVarRW(mainBar, "Obj Rotation", TW_TYPE_QUAT4F, &g_Rotation,
			" opened=true help='Change the object orientation.' ");

		TwAddSeparator(mainBar, "", NULL);

		// 도형 Rotation 모드
		TwEnumVal rotationEV[] = { { Scene::ROT_OFF, "Stopped" },
		{ Scene::ROT_CW,  "Clockwise" },
		{ Scene::ROT_CCW, "Counter-clockwise" } };
		TwType rotationType = TwDefineEnum("Rotation Mode", rotationEV, 3);
		TwAddVarRW(mainBar, "Obj Rotation Scene", rotationType, &scene.Rotation,
			" keyIncr=Backspace keyDecr=SHIFT+Backspace help='Stop or change the rotation mode.' ");



		scene.Init(true);


		
	}

	virtual ~SceneManager()
	{
	}

	Scence_mirror* scence_mirror = new Scence_mirror();

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	// 필요한 설정값 초기화
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	void Init(QuadCore::Camera* camera)
	{
		m_scene_list.push_back(new Scene_SkyBox);

		m_scene_list.push_back(new Scene_main);

		//m_scene_list.push_back(new Scene_basicObjects);
		//m_scene_list.push_back(new Scence_moving_wall);
		//m_scene_list.push_back(new Scence_moving_block);
		//m_scene_list.push_back(new Scence_reflect_shader);
		//m_scene_list.push_back(new Scence_multi_light);
		m_scene_list.push_back(new Scence_SolarSystem); 

		//m_scene_list.push_back(new Scence_mirror); // 로딩 렉 엄청 김
		m_scene_list.push_back(scence_mirror); // 로딩 렉 엄청 김


		m_scene_list.at(0)->SetEnable(true);	//Scene_SkyBox

		m_scene_list.at(1)->SetEnable(true);	//Scene_main

		m_scene_list.at(2)->SetEnable(true);	//Scene_basicObjects
		m_scene_list.at(3)->SetEnable(true);	//Scence_moving_wall
		//m_scene_list.at(4)->SetEnable(false);	//Scence_moving_block
		//m_scene_list.at(5)->SetEnable(false);	//Scence_moving_cube
		//m_scene_list.at(6)->SetEnable(false);	//Scence_reflect_shader
		//m_scene_list.at(7)->SetEnable(false);	//Scence_multi_light
		//m_scene_list.at(8)->SetEnable(true);	//Scence_SolarSystem
		//m_scene_list.at(9)->SetEnable(false);	//Scence_mirror

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		dMap.Init(camera);
		dMap.SetProperty(100, 1.0f, glm::vec4(0.7f, 0.7f, 0.7f, 3.0f));		// Draw Map

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

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

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	// 장면을 재생한다.
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	void Play()
	{		
		counter += 0.05f;
		QuadCore::iScene::SetCounter(counter);

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		//dMap.DrawPlane();		// Draw Map	

		
		scence_mirror->KeyInput(m_cur_key);

		
		// TwSimple 배경추가
		//display.Clear(scene.BgColor0[0], scene.BgColor0[1], scene.BgColor0[2], 1);	// 배경 초기화	
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		for (int i = 0; i < m_scene_list.size(); i++)
		{
			m_scene_list.at(i)->Play();
		}

		// Rotate model	// TwSimple Rotation 추가
		scene.dt = glfwGetTime() - scene.time;
		if (scene.dt < 0) scene.dt = 0;
		scene.time += scene.dt;
		scene.turn += scene.speed*scene.dt;

		///
		// Move lights
		scene.Update(scene.time);

		// Draw Light UI 
		scene.Draw();

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		// Draw tweak bar UI
		TwDraw();
	}
	
private:
	float counter = 0.0f;

	std::vector<QuadCore::iScene*> m_scene_list;

	QuadCore::DrawMap dMap;
};


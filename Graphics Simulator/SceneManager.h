#pragma once

#include "ShapeManager.h"
#include "iScene.h"

#include "World_coordinate.h"
#include "miniUI_coordinate.h"

#include "DrawMap.h"

#include "Scene_main.h"

// 衛釭葬螃
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

#include "UI_TwBar.h"


#include "Render_Mode.h"



class SceneManager
{
public:

	//float bgColor[3] = { 0.1f, 0.2f, 0.4f };         // Background color 

	float m_bgColor[3] = { 0.0f / 255.0f, 6.0f / 255.0f, 106.0f / 255.0f };	// Background color 
	bool IsDefault = false;	
	bool m_scene_1 = false;	// skybox
	bool m_scene_2 = false;	// solar system
	bool m_scene_3 = false;	// show room

	bool m_stopper = false;

	bool switch_mini_coordinate = false;
	bool switch_world_coordinate = false;
	bool switch_local_coordinate = false;
	bool switch_grid_map = false;

	unsigned char cubeColor[4] = { 255, 0, 0, 128 }; // Model color (32bits RGBA)
	float g_Rotation[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float g_LightDirection[3] = { -0.57735f, -0.57735f, -0.57735f };

	Scene scene;
	TwBar *mainUI; // play л熱縑憮 UI 碳楝螃紫煙 ж晦嬪п 蹺陛. 
	TwBar *objectUI;
	
	//嘐楝壁 UI
	TwBar *mirrorUI;
	bool mirrorUIenable = false; // 棻艇 壁縑憮 OnOffж晦 嬪и 滲熱
	bool mirrorcheckbutton = false;
	
	//鷓曄啗壁 UI
	TwBar *solarUI;
	bool solarUIenable = false; // 棻艇 壁縑憮 OnOffж晦 嬪и 滲熱
	float rotspeed = 0.1;
	float rotspeed_object = 0;


	SceneManager()
	{

		// Initialize AntTweakBar
		TwInit(TW_OPENGL, NULL);

		// UI_Bar 檜葷 // Create a tweak bar
		TwBar *mainBar = TwNewBar("Main");
		TwDefine(" Main label='MAIN' fontsize=3 size ='245 400' position='30 30' alpha=0 help='Use this bar to edit the main in the scene.' ");

		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
		// 衛除
		TwAddVarRO(mainBar, "Run Time", TW_TYPE_DOUBLE, &scene.time, "precision=1 help='Time (in seconds).' ");

		TwAddVarRW(mainBar, "Counter", TW_TYPE_FLOAT, &counter, "precision=1 help='Time (in seconds).' ");
		TwAddVarRW(mainBar, "Stop", TW_TYPE_BOOLCPP, &m_stopper, "key=P help='mini_coordinate' ");


		TwAddSeparator(mainBar, "", NULL);	// 嬴楚薹縑 line儅撩
		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

		TwAddVarRW(mainBar, "Set Default", TW_TYPE_BOOLCPP, &IsDefault, "key=R help='set to default mode.' ");

		// 寡唳 滲唳ж朝 詭景, SceneNumber 滲熱蒂 褻瞰л
		TwAddVarRW(mainBar, "Background Num", TW_TYPE_INT32, &scene.BackgroundNum, " min=0 max=3 help='Change Background' ");

		// 壁 滲唳ж朝 詭景, SceneNumber 滲熱蒂 褻瞰л
		scene.SceneNumber = 0;
		TwAddVarRW(mainBar, "Animation Num", TW_TYPE_INT32, &scene.SceneNumber, " min=0 max=8 help='Change Scene' ");
		//TwAddVarRW(TwBar *bar, const char *name, TwType type, void *var, const char *def);

		TwAddVarRW(mainBar, " 1. Skybox", TW_TYPE_BOOLCPP, &m_scene_1, "key=1 help='Scene1. SkyBox' ");
		TwAddVarRW(mainBar, " 2. Solar System", TW_TYPE_BOOLCPP, &m_scene_2, "key=2 help='Scene2. Solar System' ");
		TwAddVarRW(mainBar, " 3. Room", TW_TYPE_BOOLCPP, &m_scene_3, "key=3 help='Scene3. Show Room' ");

		TwAddSeparator(mainBar, "", NULL);
		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

		///TwAddButton(mainBar, "Button", TW_TYPE_CDSTRING, , );
		
		// Background 鏽楝 滲唳
		TwAddVarRW(mainBar, "Background Color", TW_TYPE_COLOR3F, &m_bgColor, " opened=true help='Change the top background color.' ");
		TwAddSeparator(mainBar, "", NULL);


		
		// 
		TwAddVarRW(mainBar, "Mini Coordinate", TW_TYPE_BOOLCPP, &switch_mini_coordinate, "key=B help='mini_coordinate' ");
		TwAddVarRW(mainBar, "World Coordinate", TW_TYPE_BOOLCPP, &switch_world_coordinate, "key=N help='world_coordinate' ");
		TwAddVarRW(mainBar, "Local Coordinate", TW_TYPE_BOOLCPP, &switch_local_coordinate, "key=L help='world_coordinate' ");
		TwAddVarRW(mainBar, "Grid World Map", TW_TYPE_BOOLCPP, &switch_grid_map, "key=M help='draw_Grid_Map' ");

		//TwAddSeparator(mainBar, "", NULL);
		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
		
		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
				

		scene.Init(true);

		mainUI = mainBar; // 檜 л熱縑憮 薑曖脹 UI蒂 滲熱縑 翱唸
		
	}

	virtual ~SceneManager()
	{
	}

	//Scence_mirror* scence_mirror = new Scence_mirror();

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	// в蹂и 撲薑高 蟾晦��
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
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
		m_scene_list.push_back(new Scence_mirror);			// 1.SkyBox
		m_scene_list.push_back(new Scence_SolarSystem);		// 2.Solar System
		m_scene_list.push_back(new Scene_ShowRoom);			// 3.Show Room
		m_scene_list.push_back(new Scence_moving_wall);		// 維曖 嬪纂 撲貲й 陽 餌辨
		m_scene_list.push_back(new Scence_moving_block);	// �蛾戲� 賅曄戲煎 螃粽薛お 寡纂п爾賊 謠擊蛭
		m_scene_list.push_back(new Scene_basicObjects);		// 棻曄и 螃粽薛お縑憮 維檜 瞳辨腎朝 賅蝗 衛翱
		m_scene_list.push_back(new Scence_multi_light);		// 罹楝偃曖 僭羹縑 瞳辨腎朝 維
		m_scene_list.push_back(new Scene_main);
		m_scene_list.push_back(new Scene_main);
		m_scene_list.push_back(new Scene_main);
		m_scene_list.push_back(new Scene_main);
		///m_scene_list.push_back(new Scence_reflect_shader);	// 嘐餌辨 纔蝶お 幗瞪
				
		for (int i = 0; i < m_scene_list.size(); i++)
		{
			m_scene_list.at(i)->SetEnable(true);
		}

		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

		dMap.Init(camera);
		dMap.SetProperty(100, 1.0f, glm::vec4(0.7f, 0.7f, 0.7f, 3.0f));		// Draw Map

		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
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

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	// 嘐葬 撲薑脹 衛釭葬螃蒂 摹鷗и棻.
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	void Select_Scene()
	{
		//// 壁 醞犒摹鷗 寰腎紫煙 籀葬й 匙
		switch (scene.BackgroundNum_prev)
		{
		case 1:
			if (m_scene_1 == true && m_scene_2 == true)
			{
				m_scene_1 = false;
				scene.BackgroundNum = 2;
			}
			if (m_scene_3 == true && m_scene_1 == true)
			{
				m_scene_1 = false;
				scene.BackgroundNum = 3;
			}
			break;
		case 2:
			if (m_scene_1 == true && m_scene_2 == true)
			{
				m_scene_2 = false;
				scene.BackgroundNum = 1;
			}
			if (m_scene_2 == true && m_scene_3 == true)
			{
				m_scene_2 = false;
				scene.BackgroundNum = 3;
			}
			break;
		case 3:
			if (m_scene_2 == true && m_scene_3 == true)
			{
				m_scene_3 = false;
				scene.BackgroundNum = 2;
			}
			if (m_scene_3 == true && m_scene_1 == true)
			{
				m_scene_3 = false;
				scene.BackgroundNum = 1;
			}
			break;
		}

		// 壁 摹鷗璽
		if (m_scene_1) {
			scene.BackgroundNum_prev = 1;
			scene.BackgroundNum = 1;

			scene.SceneNumber = 1;	// 錳ж朝 壁戲煎 撲薑
		}
		if (m_scene_2) {
			scene.BackgroundNum_prev = 2;
			scene.BackgroundNum = 2;

			scene.SceneNumber = 2;	// 錳ж朝 壁戲煎 撲薑
		}
		if (m_scene_3) {
			scene.BackgroundNum_prev = 3;
			scene.BackgroundNum = 3;

			scene.SceneNumber = 3;	// 錳ж朝 壁戲煎 撲薑
		}

		if (IsDefault)
		{
			m_scene_1 = false;
			m_scene_2 = false;
			m_scene_3 = false;

			scene.BackgroundNum = 0;
			scene.SceneNumber = 0;
		}
	}

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	// 濰賊擊 營儅и棻.
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	void Play()
	{
		if(!m_stopper)
			counter += 0.05f;
		QuadCore::iScene::SetCounter(counter);

		m_display->Clear(m_bgColor[0], m_bgColor[1], m_bgColor[2], 1.0f);

		this->Select_Scene();

		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
		
		if (switch_grid_map)
		{
			dMap.DrawPlane();		// Draw Map	
		}
				

		//scence_mirror->KeyInput(m_cur_key);		

		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
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
			float final_speed = 0;
			
			//UI 高縑 蜃朝 壁虜 Ы溯檜
			if (i == scene.SceneNumber)
			{
				int j = i;

				m_scene_list.at(j)->Set_LocalCoordinate(switch_local_coordinate);

				switch (i)
				{
				case 0:								// 0.Default(none)
					TurnOffMirrorUI();
					TurnOffSolarUI();
					TurnOffRoomUI();
					m_scene_list.at(j)->Play();
					break;
				case 1:								// 1.SkyBox
					TurnOnMirrorUI();
					TurnOffSolarUI();
					TurnOffRoomUI();
					m_scene_list.at(j)->Play(scene.Spheres);
					break;
				case 2:								// 2.Solar System
					//m_scene_list.at(j)->Play();
					TurnOffMirrorUI();
					TurnOnSolarUI();
					TurnOffRoomUI();
					m_scene_list.at(j)->Play(rotspeed, pos, ambient, diffuse, specular);
					break;
				case 3:								// 3.Show Room
					TurnOffMirrorUI();
					TurnOffSolarUI();
					TurnOnRoomUI();
					//m_scene_list.at(j)->Play();
					final_speed = rotspeed_object;

					if (scene.Rotation == Scene::ROT_OFF)
						final_speed = 0;
					else if (scene.Rotation == Scene::ROT_CW)
						final_speed = -rotspeed_object;
					else if (scene.Rotation == Scene::ROT_CCW)
						final_speed = +rotspeed_object;


					if (m_stopper)
						final_speed = 0;

					if (reset_rotation)
					{
						g_Rotation[0] = 0.0f;
						g_Rotation[1] = 0.0f;
						g_Rotation[2] = 0.0f;
						reset_rotation = false;
					}

					if(IsChanged_Reder_Mode())
						m_scene_list.at(j)->Set_RenderMode(object_mode, shader_mode, texture_mode);

					m_scene_list.at(j)->Play(g_Rotation, final_speed, pos, ambient, diffuse, specular);
					break;
				default:
					TurnOffMirrorUI();
					TurnOffSolarUI();
					TurnOffRoomUI();
					m_scene_list.at(j)->Play();
					break;
				}
			}
		}

		// Rotate model	// TwSimple Rotation 蹺陛
		scene.dt = glfwGetTime() - scene.time;
		if (scene.dt < 0) scene.dt = 0;
		scene.time += scene.dt;
		scene.turn += scene.speed*scene.dt;

		///
		// Move lights
		scene.Update(scene.time);

		// Draw Light UI 
		scene.Draw();

		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
		// Draw tweak bar UI
		TwDraw();


		//////////////////////////////////////////////////////////////////////
		////// UI 謝ル啗 斜葬晦
		m_world_coordinate.Draw(m_camera, switch_world_coordinate);
		m_mini_coordinate.Draw(m_camera, switch_mini_coordinate);
		//////////////////////////////////////////////////////////////////////
	}
	
private:
	float counter = 0.0f;

	std::vector<QuadCore::iScene*> m_background_list;
	std::vector<QuadCore::iScene*> m_scene_list;

	QuadCore::DrawMap dMap;

	QuadCore::Camera* m_camera;
	QuadCore::Display* m_display;

	QuadCore::miniUI_coordinate m_mini_coordinate;
	QuadCore::World_coordinate m_world_coordinate;

	void TurnOnMirrorUI()
	{
		if (!mirrorUIenable)
		{
			TwBar *mirrorBar = TwNewBar("Skybox");
			TwDefine(" Skybox label='SKYBOX' size ='245 400' position='760 30' alpha=0 help='Use this bar to edit object in the scene.' ");
			//TwDefine(" Skybox label='SKYBOX' size ='245 400' position='1340 30' alpha=0 help='Use this bar to edit object in the scene.' ");
			//TwAddVarRW(mirrorBar, "BOOLBUTTON", TW_TYPE_BOOLCPP, &mirrorcheckbutton, " help='control' ");
			//TwAddVarRW(mirrorBar, "Sphere Num", TW_TYPE_INT32, &scene.Spheres, " min=0 max=180 help='Change a number of sphere' ");
			TwAddVarRW(mirrorBar, "Sphere Num", TW_TYPE_INT32, &scene.Spheres, " min=0 max=32 help='Change a number of sphere' ");

			mirrorUI = mirrorBar;

			mirrorUIenable = true;
		}
	}
	void TurnOffMirrorUI()
	{
		if(mirrorUIenable)
			TwDeleteBar(mirrorUI);

		mirrorUIenable = false;
	}

	void TurnOnSolarUI()
	{
		if (!solarUIenable)
		{
			TwBar *solarBar = TwNewBar("Solar");
			TwDefine(" Solar label='SOLAR SYSTEM' size ='245 400' position='760 30' alpha=0 help='Use this bar to edit object in the scene.' ");
			//TwDefine(" Solar label='SOLAR SYSTEM' size ='245 400' position='1340 30' alpha=0 help='Use this bar to edit object in the scene.' ");
			//TwAddVarRW(solarBar, "BOOLBUTTON", TW_TYPE_BOOLCPP, &mirrorcheckbutton, " help='control' ");
			TwAddVarRW(solarBar, "Rotation Speed", TW_TYPE_FLOAT, &rotspeed,
				" min=0.01 max=2.0 step=0.01 help='Change a number of sphere' ");

			solarUI = solarBar;

			solarUIenable = true;
		}
	}
	void TurnOffSolarUI()
	{
		if(solarUIenable)
			TwDeleteBar(solarUI);

		solarUIenable = false;
	}

	bool roomUIenable = false;

public:


private:
	OBJECT_MODE check_object_mode;
	SHADER_MODE check_shader_mode;
	TEXTURE_MODE check_texture_mode;

	OBJECT_MODE object_mode;
	SHADER_MODE shader_mode;
	TEXTURE_MODE texture_mode;

	bool IsChanged_Reder_Mode()
	{
		if ((object_mode != check_object_mode)
			|| (shader_mode != check_shader_mode)
			|| (texture_mode != check_texture_mode))
		{
			check_object_mode = object_mode;
			check_shader_mode = shader_mode;
			check_texture_mode = texture_mode;
			printf("Changed Render Mode\n");
			return true;
		}
		return false;
	}


private:
	void TurnOnRoomUI()
	{
		if (!roomUIenable)
		{
			TwBar *objectBar = TwNewBar("Object");
			TwDefine(" Object label='OBJECT' size ='300 400' position='705 30' alpha=0 help='Use this bar to edit object in the scene.' ");
			//TwDefine(" Object label='OBJECT' size ='300 400' position='1285 30' alpha=0 help='Use this bar to edit object in the scene.' ");
			//TwDefine(" Object label='OBJECT' size ='245 400' position='1640 30' alpha=0 help='Use this bar to edit object in the scene.' ");

			//TwAddSeparator(mainBar, "", NULL);

			
			TwEnumVal objectEV[] = {
				{ OBJECT_MODE::Bunny, "Bunny" },
				{ OBJECT_MODE::Lucy,  "Lucy" },
				{ OBJECT_MODE::Lucycat, "Lucycat" },
				{ OBJECT_MODE::Lucycat_voronol, "Lucycat_voronol" },

				{ OBJECT_MODE::bear, "bear" },
				{ OBJECT_MODE::nanosuit, "nanosuit" },

				//glove, chair, WineGlasses,
				{ OBJECT_MODE::glove, "glove" },
				{ OBJECT_MODE::chair, "chair" },
				{ OBJECT_MODE::WineGlasses, "WineGlasses" },

				//Torus, Cube, Sphere, Icosphere, CubeHollow,
				{ OBJECT_MODE::Torus, "Torus" },
				{ OBJECT_MODE::Cube, "Cube" },
				{ OBJECT_MODE::Sphere, "Sphere" },
				{ OBJECT_MODE::Icosphere, "Icosphere" },
				{ OBJECT_MODE::CubeHollow, "CubeHollow" },


			};
			TwType objectType = TwDefineEnum("Object Mode", objectEV, OBJECT_MODE::OBJECT_MODE_SIZE);
			TwAddVarRW(objectBar, "Select Object", objectType, &object_mode,
				" keyIncr=H keyDecr=Y help='...' ");

			TwEnumVal shaderEV[] = {
										{ SHADER_MODE::Phong, "Phong Shading" },
										{ SHADER_MODE::Multi,  "Multi Shading" },
										{ SHADER_MODE::Rim, "Rim Shading" }
									};
			TwType shaderType = TwDefineEnum("Shader Mode", shaderEV, SHADER_MODE::SHADER_MODE_SIZE);
			TwAddVarRW(objectBar, "Select Shader", shaderType, &shader_mode,
				" keyIncr=J keyDecr=U help='...' ");

			TwEnumVal textureEV[] = {
				{ TEXTURE_MODE::Bricks, "Bricks" },
				{ TEXTURE_MODE::Skyblue,  "Skyblue" },
				{ TEXTURE_MODE::Formula, "Formula" },

				{ TEXTURE_MODE::dark_spot, "dark_spot" },
				{ TEXTURE_MODE::diamond, "diamond" },
				{ TEXTURE_MODE::grain_grass, "grain_grass" },
				{ TEXTURE_MODE::iron, "iron" },
				{ TEXTURE_MODE::lines_dark, "lines_dark" },
				{ TEXTURE_MODE::metal, "metal" },
				{ TEXTURE_MODE::moon, "moon" },

				{ TEXTURE_MODE::slime, "slime" },
				{ TEXTURE_MODE::surface_dark, "surface_dark" },
				{ TEXTURE_MODE::surface_gold_shine, "surface_gold_shine" },
				{ TEXTURE_MODE::pastel, "pastel" },
				{ TEXTURE_MODE::wall_brick, "wall_brick" },
				{ TEXTURE_MODE::wood, "wood" },
				/*
				dark_spot, diamond, grain_grass, iron, lines_dark, metal, moon,
				slime, surface_dark, surface_gold_shine, pastel, wall_brick, wood,
				*/
			};
			TwType textureType = TwDefineEnum("Texture Mode", textureEV, TEXTURE_MODE::TEXTURE_MODE_SIZE);
			TwAddVarRW(objectBar, "Select Texture", textureType, &texture_mode,
				" keyIncr=K keyDecr=I help='...' ");


			//// Cube 鏽楝 滲唳
			//TwAddVarRW(objectBar, "Obj Color", TW_TYPE_COLOR32, &cubeColor,
			//	"alpha help='Color and transparency of the cube.' ");

			TwAddSeparator(objectBar, "", NULL);

			// 紫⑽ Rotation Speed 褻薑 // Its key shortcuts are [s] and [S].
			TwAddVarRW(objectBar, "Obj Rotation Speed", TW_TYPE_FLOAT, &rotspeed_object,
				" min=0 max=10 step=0.01 keyDecr=, keyIncr=. help='Rotation speed (turns/second)' ");

			TwAddSeparator(objectBar, "", NULL);

			TwAddVarRW(objectBar, "Reset Rotation", TW_TYPE_BOOLCPP, &reset_rotation, "key=C help='reset_rotation' ");

			// 紫⑽ Rotation 
			TwAddVarRW(objectBar, "Obj Rotation", TW_TYPE_QUAT4F, &g_Rotation,
				" opened=true help='Change the object orientation.' ");

			TwAddSeparator(objectBar, "", NULL);
			

			// 紫⑽ Rotation 賅萄
			TwEnumVal rotationEV[] = { { Scene::ROT_OFF, "Stopped" },
			{ Scene::ROT_CW,  "Clockwise" },
			{ Scene::ROT_CCW, "Counter-clockwise" } };
			TwType rotationType = TwDefineEnum("Rotation Mode", rotationEV, 3);
			TwAddVarRW(objectBar, "Obj Rotation Scene", rotationType, &scene.Rotation,
				" keyIncr=X keyDecr=Z help='Stop or change the rotation mode.' ");

			objectUI = objectBar;

			roomUIenable = true;

			///
			check_object_mode = object_mode;
			check_shader_mode = shader_mode;
			check_texture_mode = texture_mode;
		}
	}

	bool reset_rotation = false;

	void TurnOffRoomUI()
	{
		if (roomUIenable)
			TwDeleteBar(objectUI);

		roomUIenable = false;
	}

};


#pragma once


#include <AntTweakBar.h>
#include <GLEW-2.0.0_x64/GL/glew.h>

#include "UI_TwBar.h"

#include "Render_Mode.h"


#define _snprintf snprintf


struct MultiLight
{
	char    Name[4];				// light short name (will be named "1", "2", "3",...)
	float posX;
	float posY;
	float posZ;
	float ambient[4];
	float diffuse[4];
	float specular[4];
};


class Menu
{
public:
	Menu()
	{
		// Set scene members.
		// The scene will be created by Scene::Init( )
		//Wireframe = false;
		NumLights = 0;

		maxLights = 0;
		lightsBar = NULL;

		Create_mainUI();
	}

	virtual ~Menu()
	{
	}

	void Init(bool changeLights)
	{
		// Get the max number of lights allowed by the graphic card
		glGetIntegerv(GL_MAX_LIGHTS, &maxLights);
		if (maxLights>3)
			maxLights = 3;

		// Create the lights array
		if (multilights == NULL && maxLights > 0)
		{
			multilights = new MultiLight[maxLights];
			NumLights = 3;               // default number of lights
			if (NumLights>maxLights)
				NumLights = maxLights;
			changeLights = true;         // force lights initialization

										 // Create a tweak bar for lights
			CreateBar();
		}

		// (Re)initialize lights if needed (uses random values)
		if (changeLights)
		{
			for (int i = 0; i < maxLights; ++i)
			{
				multilights[i].posX = 0;
				multilights[i].posY = 0;
				multilights[i].posZ = 0;
				multilights[i].ambient[0] = 0.1f;
				multilights[i].ambient[1] = 0.1f;
				multilights[i].ambient[2] = 0.1f;
				multilights[i].ambient[3] = 1;
				multilights[i].diffuse[0] = (i == 0) ? 0.8f : 0.4f;
				multilights[i].diffuse[1] = (i == 1) ? 0.8f : 0.4f;
				multilights[i].diffuse[2] = (i == 2) ? 0.8f : 0.4f;
				multilights[i].diffuse[3] = 1;
				multilights[i].specular[0] = (i == 0) ? 1.0f : 0.5f;
				multilights[i].specular[1] = (i == 1) ? 1.0f : 0.5f;
				multilights[i].specular[2] = (i == 2) ? 1.0f : 0.5f;
				multilights[i].specular[3] = 1;
			}
		}

	}

	float counter_speed = 1.0f;

	void SetTime(double sysyem_time)
	{
		// Rotate model	// TwSimple Rotation 추가
		dt = sysyem_time - time;
		if (dt < 0) dt = 0;
		time += dt;
		turn += speed*dt;
	}

	// Light Bar 생성
	void CreateBar()
	{
		// Light parameter
		float g_LightDirection[] = { -0.57735f, -0.57735f, -0.57735f };

		// Bar 이름
		lightsBar = TwNewBar("Lights");
		TwDefine(" Lights label='LIGHTS' size ='245 450' position='30 510' alpha=0 help='Use this bar to edit the lights in the scene.' ");
		//TwDefine(" Lights label='LIGHTS' size ='245 450' position='30 450' alpha=0 help='Use this bar to edit the lights in the scene.' ");

		// 추가 될 각 multilight의 속성 
		TwStructMember lightMembers[] = // Light structure
		{
			{ "Pos - X",     TW_TYPE_FLOAT, offsetof(MultiLight, posX),     " min=-500.00 max=500.00 step=0.1 help='Light PositionX.' " },
			{ "Pos - Y",     TW_TYPE_FLOAT, offsetof(MultiLight, posY),     " min=-500.00 max=500.00 step=0.1 help='Light PositionY.' " },
			{ "Pos - Z",     TW_TYPE_FLOAT, offsetof(MultiLight, posZ),     " min=-500.00 max=500.00 step=0.1 help='Light PositionZ.' " },

			{ "Ambient",     TW_TYPE_COLOR3F, offsetof(MultiLight, ambient),     " help='Light Ambient.' " },
			{ "Diffuse",     TW_TYPE_COLOR3F, offsetof(MultiLight, diffuse),     " help='Light Diffuse.' " },
			{ "Specular",     TW_TYPE_COLOR3F, offsetof(MultiLight, specular),     " help='Light Specular.' " }			// Light::Speed is made read-only
		};
		TwType lightType = TwDefineStruct("MultiLight", lightMembers, 6, sizeof(MultiLight), NULL, NULL);  // struct defined by the lightMembers array

																										   // light 갯수만큼 메뉴 생성
		for (int i = 0; i<3; ++i)  // Add 'maxLights' variables of type lightType; 
		{   // unused lights variables (over NumLights) will hidden by Scene::Update( )
			_snprintf(multilights[i].Name, sizeof(multilights[i].Name), "%d", i + 1);							// Create a name for each light ("1", "2", "3",...)
			TwAddVarRW(lightsBar, multilights[i].Name, lightType, &multilights[i], " opened=true group='Edit lights' ");  // Add a lightType variable and group it into the 'Edit lights' group

																														  // Set 'label' and 'help' parameters of the light
			char paramValue[64];
			_snprintf(paramValue, sizeof(paramValue), "Light #%d", i + 1);
			TwSetParam(lightsBar, multilights[i].Name, "label", TW_PARAM_CSTRING, 1, paramValue); // Set label
			_snprintf(paramValue, sizeof(paramValue), "Parameters of the light #%d", i + 1);
			TwSetParam(lightsBar, multilights[i].Name, "help", TW_PARAM_CSTRING, 1, paramValue);  // Set help
		}

		//TwAddSeparator(lightsBar, "", NULL);

	}

	enum    RotMode { ROT_OFF, ROT_CW, ROT_CCW };
	RotMode Rotation = ROT_CCW;				// scene rotation mode (off, clockwise, counter-clockwise)

public:
	double speed = 0.3; // Model rotation speed
	double time = 0, dt;// Current time and enlapsed time
	double turn = 0;    // Model turn counter

	//본 프로젝트에 맞춘 추가적인 변수들
	int BackgroundNum_prev = 0;
	int BackgroundNum = 0;
	int SceneNumber = 0;
	int Spheres = 5;
	MultiLight * multilights;

public:
	int     NumLights;				// number of dynamic lights
private:
	int     maxLights;                      // maximum number of dynamic lights allowed by the graphic card
	TwBar * lightsBar;                      // pointer to the tweak bar for lights created by CreateBar()

public:
	//미러씬 UI
	TwBar *mirrorUI;
	bool mirrorUIenable = false; // 다른 씬에서 OnOff하기 위한 변수
	bool mirrorcheckbutton = false;
	bool roomUIenable = false;

	//태양계씬 UI
	TwBar *solarUI;
	bool solarUIenable = false; // 다른 씬에서 OnOff하기 위한 변수
	float rotspeed = 0.1f;
	float rotspeed_object = 0.0f;

public:
	void TurnOnMirrorUI()
	{
		if (!mirrorUIenable)
		{
			TwBar *mirrorBar = TwNewBar("Skybox");
			TwDefine(" Skybox label='SKYBOX' size ='245 400' position='760 30' alpha=0 help='Use this bar to edit object in the scene.' ");
			//TwDefine(" Skybox label='SKYBOX' size ='245 400' position='1340 30' alpha=0 help='Use this bar to edit object in the scene.' ");
			//TwAddVarRW(mirrorBar, "BOOLBUTTON", TW_TYPE_BOOLCPP, &mirrorcheckbutton, " help='control' ");
			//TwAddVarRW(mirrorBar, "Sphere Num", TW_TYPE_INT32, &scene.Spheres, " min=0 max=180 help='Change a number of sphere' ");
			TwAddVarRW(mirrorBar, "Sphere Num", TW_TYPE_INT32, &Spheres, " min=0 max=32 help='Change a number of sphere' ");

			mirrorUI = mirrorBar;

			mirrorUIenable = true;
		}
	}
	void TurnOffMirrorUI()
	{
		if (mirrorUIenable)
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
		if (solarUIenable)
			TwDeleteBar(solarUI);

		solarUIenable = false;
	}


	void TurnOnRoomUI()
	{
		if (!roomUIenable)
		{
			TwBar *objectBar = TwNewBar("Object");
			TwDefine(" Object label='OBJECT' size ='300 600' position='705 30' alpha=0 help='Use this bar to edit object in the scene.' ");
			//TwDefine(" Object label='OBJECT' size ='300 400' position='705 30' alpha=0 help='Use this bar to edit object in the scene.' ");
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

				{ OBJECT_MODE::Custom1, "Custom1" },
				{ OBJECT_MODE::Custom2, "Custom2" },
				{ OBJECT_MODE::Custom3, "Custom3" },

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


			//// Cube 컬러 변경
			//TwAddVarRW(objectBar, "Obj Color", TW_TYPE_COLOR32, &cubeColor,
			//	"alpha help='Color and transparency of the cube.' ");

			TwAddSeparator(objectBar, "", NULL);

			// 도형 Rotation Speed 조정 // Its key shortcuts are [s] and [S].
			TwAddVarRW(objectBar, "Obj Rotation Speed", TW_TYPE_FLOAT, &rotspeed_object,
				" min=0 max=10 step=0.01 keyDecr=, keyIncr=. help='Rotation speed (turns/second)' ");

			TwAddSeparator(objectBar, "", NULL);

			TwAddVarRW(objectBar, "Reset Rotation", TW_TYPE_BOOLCPP, &reset_rotation, "key=C help='reset_rotation' ");

			// 도형 Rotation 
			TwAddVarRW(objectBar, "Obj Rotation", TW_TYPE_QUAT4F, &g_Rotation,
				" opened=true help='Change the object orientation.' ");

			TwAddSeparator(objectBar, "", NULL);


			// 도형 Rotation 모드
			TwEnumVal rotationEV[] = { { Menu::ROT_OFF, "Stopped" },
			{ Menu::ROT_CW,  "Clockwise" },
			{ Menu::ROT_CCW, "Counter-clockwise" } };
			TwType rotationType = TwDefineEnum("Rotation Mode", rotationEV, 3);
			TwAddVarRW(objectBar, "Obj Rotation Scene", rotationType, &Rotation,
				" keyIncr=X keyDecr=Z help='Stop or change the rotation mode.' ");

			TwAddSeparator(objectBar, "", NULL);

			TwAddVarRW(objectBar, "Pause Effect", TW_TYPE_BOOLCPP, &is_effect_pause, "key=0 help='Pause Effect' ");
			TwAddVarRW(objectBar, "Object Explode", TW_TYPE_BOOLCPP, &is_explode, "help='effect_explode' ");
			TwAddVarRW(objectBar, "Explode Factor", TW_TYPE_FLOAT, &m_explode_factor, " min=0.00 max=10.00 step=0.1 help='explode factor' ");
			TwAddVarRW(objectBar, "Explode Speed", TW_TYPE_FLOAT, &m_explode_speed, " min=0.00 max=10.00 step=0.1 help='explode speed' ");
			TwAddVarRW(objectBar, "Normal Viewer", TW_TYPE_BOOLCPP, &is_normal_view, "help='effect_normal' ");
			TwAddVarRW(objectBar, "Normal Length", TW_TYPE_FLOAT, &m_normal_length, " min=0.00 max=2.00 step=0.001 help='Resize Normal Length' ");

			TwAddSeparator(objectBar, "", NULL);
			TwAddVarRW(objectBar, "Polygon Mode", TW_TYPE_BOOLCPP, &m_poly_mode, "help='polygon_mode' ");

			TwAddVarRW(objectBar, "Tess Level Inner", TW_TYPE_FLOAT, &m_tess_level_inner, " min=1.00 help='' ");
			TwAddVarRW(objectBar, "Tess Level Outer", TW_TYPE_FLOAT, &m_tess_level_outer, " min=1.00 help='' ");
			TwAddVarRW(objectBar, "Tess Level Scale", TW_TYPE_FLOAT, &m_tess_level_scale, " min=0.00 help='' ");




			objectUI = objectBar;

			roomUIenable = true;

			///
			check_object_mode = object_mode;
			check_shader_mode = shader_mode;
			check_texture_mode = texture_mode;

			updated_normal_mode = is_normal_view;
		}
	}

	bool m_wireframe = false;
	bool m_poly_mode = false;

	TwBar *mainUI; // play 함수에서 UI 불러오도록 하기위해 추가. 
	TwBar *objectUI;
	bool m_stopper = false;
	float counter = 0.0f;


	float m_bgColor[3] = { 0.0f / 255.0f, 6.0f / 255.0f, 106.0f / 255.0f };	// Background color 


	bool IsDefault = false;
	bool m_scene_1 = false;	// skybox
	bool m_scene_2 = false;	// solar system
	bool m_scene_3 = false;	// show room

	bool m_counter_reset = false;

	bool switch_mini_coordinate = false;
	bool switch_world_coordinate = false;
	bool switch_local_coordinate = false;
	bool switch_grid_map = false;


	void Create_mainUI()
	{
		// Initialize AntTweakBar
		TwInit(TW_OPENGL, NULL);

		// UI_Bar 이름 // Create a tweak bar
		TwBar *mainBar = TwNewBar("Main");
		TwDefine(" Main label='MAIN' fontsize=3 size ='245 460' position='30 30' alpha=0 help='Use this bar to edit the main in the scene.' ");
		//TwDefine(" Main label='MAIN' fontsize=3 size ='245 400' position='30 30' alpha=0 help='Use this bar to edit the main in the scene.' ");

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		// 시간
		TwAddVarRO(mainBar, "Run Time", TW_TYPE_DOUBLE, &time, "precision=1 help='Time (in seconds).' ");

		TwAddVarRW(mainBar, "Counter", TW_TYPE_FLOAT, &counter, "precision=1 help='Time (in seconds).' ");
		TwAddVarRW(mainBar, "Speed", TW_TYPE_FLOAT, &counter_speed, "precision=1 help='Time (in seconds).' ");
		TwAddVarRW(mainBar, "Stop", TW_TYPE_BOOLCPP, &m_stopper, "key=P help='mini_coordinate' ");
		TwAddVarRW(mainBar, "Reset", TW_TYPE_BOOLCPP, &m_counter_reset, "key=4 precision=1 help='Time (in seconds).' ");


		TwAddSeparator(mainBar, "", NULL);	// 아래쪽에 line생성
											//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		TwAddVarRW(mainBar, "Wireframe", TW_TYPE_BOOLCPP, &m_wireframe, "help='wireframe' ");
		TwAddVarRW(mainBar, "Set Default", TW_TYPE_BOOLCPP, &IsDefault, "key=R help='set to default mode.' ");

		// 배경 변경하는 메뉴, SceneNumber 변수를 조절함
		TwAddVarRW(mainBar, "Background Num", TW_TYPE_INT32, &BackgroundNum, " min=0 max=3 help='Change Background' ");

		// 씬 변경하는 메뉴, SceneNumber 변수를 조절함
		SceneNumber = 0;
		TwAddVarRW(mainBar, "Animation Num", TW_TYPE_INT32, &SceneNumber, " min=0 max=8 help='Change Scene' ");
		//TwAddVarRW(TwBar *bar, const char *name, TwType type, void *var, const char *def);

		TwAddVarRW(mainBar, " 1. Skybox", TW_TYPE_BOOLCPP, &m_scene_1, "key=1 help='Scene1. SkyBox' ");
		TwAddVarRW(mainBar, " 2. Solar System", TW_TYPE_BOOLCPP, &m_scene_2, "key=2 help='Scene2. Solar System' ");
		TwAddVarRW(mainBar, " 3. Room", TW_TYPE_BOOLCPP, &m_scene_3, "key=3 help='Scene3. Show Room' ");

		TwAddSeparator(mainBar, "", NULL);
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		///TwAddButton(mainBar, "Button", TW_TYPE_CDSTRING, , );

		// Background 컬러 변경
		TwAddVarRW(mainBar, "Background Color", TW_TYPE_COLOR3F, &m_bgColor, " opened=true help='Change the top background color.' ");
		TwAddSeparator(mainBar, "", NULL);



		// 
		TwAddVarRW(mainBar, "Mini Coordinate", TW_TYPE_BOOLCPP, &switch_mini_coordinate, "key=B help='mini_coordinate' ");
		TwAddVarRW(mainBar, "World Coordinate", TW_TYPE_BOOLCPP, &switch_world_coordinate, "key=N help='world_coordinate' ");
		TwAddVarRW(mainBar, "Local Coordinate", TW_TYPE_BOOLCPP, &switch_local_coordinate, "key=L help='world_coordinate' ");
		TwAddVarRW(mainBar, "Grid World Map", TW_TYPE_BOOLCPP, &switch_grid_map, "key=M help='draw_Grid_Map' ");

		//TwAddSeparator(mainBar, "", NULL);
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ


		mainUI = mainBar; // 이 함수에서 정의된 UI를 변수에 연결
	}

	void TurnOffRoomUI()
	{
		if (roomUIenable)
			TwDeleteBar(objectUI);

		roomUIenable = false;
	}


	float g_Rotation[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
public:
	bool reset_rotation = false;
	bool is_explode = false;
	bool is_normal_view = false;
	bool is_effect_pause = false;

	float m_explode_factor = 0.7f;
	float m_explode_speed = 1.0f;
	float m_normal_length = 0.02f;

	float m_tess_level_inner = 1.0f;
	float m_tess_level_outer = 1.0f;
	float m_tess_level_scale = 1.0f;

public:
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

	bool updated_normal_mode;
	bool IsChanged_Effect_Mode()
	{
		if (is_normal_view != updated_normal_mode)
		{
			updated_normal_mode = is_normal_view;
			printf("Updated Normal View Mode\n");
			return true;
		}
		return false;
	}
};




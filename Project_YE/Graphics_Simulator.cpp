#include "Graphics_Simulator.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Controls.h"
#include "DrawMap.h"
#include "UI_TwBar.h"

QuadCore::Graphics_Simulator::Graphics_Simulator()
	: display(width_window, height_window, "Graphics Simulator - QuadCore")
{
}

QuadCore::Graphics_Simulator::~Graphics_Simulator()
{
}

void QuadCore::Graphics_Simulator::Run()
{
	// 1. Object
	Mesh mesh1("../media/shape/Cube.obj");
	Mesh mesh2("../media/shape/CubeHollow.obj");
	Mesh mesh3("../media/shape/Icosphere.obj");
	

	// 2. Shader
	Shader shader1("../media/new_shader/basicShader_light");
	Shader shader2("../media/new_shader/basicShader_tex");

	// 3. Texture
	Texture texture1("../media/res/bricks.jpg");
	Texture texture2("../media/skyblue.jpg");
	Texture texture3("../media/curser.png");
	
	//4. Transform
	Transform world_transform;
	Transform UI_transform;
	Transform transform1;
	Transform transform2;
	Transform transform3;

	//5. Camera
	float aspec = (float)width_window / (float)height_window;
	Camera camera(glm::vec3(0, 0, 10), 70.0f, aspec, 0.01F, 1000.0f);

	// Controls (Mouse / Keyboard)
	Controls controls(display.GetWindow());
	Controls controller(controls, camera, world_transform);

	// Draw Map 새로 추가된 부분
	DrawMap dMap(camera);
	dMap.SetProperty(100, 1.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

	UI_transform.Init(camera.GetPos(), camera.GetForward());

	m_world_coordinates.Init(&world_transform, &camera, 5.0f);
	m_UI_coordinates.Init(&UI_transform, &camera, .1f);

	Coordinates coor_model_1;
	Coordinates coor_model_2;
	Coordinates coor_model_3;
	coor_model_1.Init(&transform1, &camera);
	coor_model_2.Init(&transform2, &camera);
	coor_model_3.Init(&transform3, &camera);

	float counter = 0.0f;

	////////////////////////////////////////////////////////////////////////////////////////////////////

	float bgColor[] = { 0.1f, 0.2f, 0.4f };         // Background color 
	unsigned char cubeColor[] = { 255, 0, 0, 128 }; // Model color (32bits RGBA)
	float g_Rotation[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float g_LightDirection[] = { -0.57735f, -0.57735f, -0.57735f };

	Scene scene;
	
	// Initialize AntTweakBar
	TwInit(TW_OPENGL, NULL);

	// UI_Bar 이름 // Create a tweak bar
	TwBar *mainBar = TwNewBar("Main");
	TwDefine(" Main label='MAIN' position='20 20' alpha=0 help='Use this bar to edit the main in the scene.' ");

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
	//////////////////////////////

	// Initialize the 3D scene
//	Scene scene;
	

	while (!display.IsClosed())
	{
		float sinCounter = sinf(counter);	// sin counter
		float cosCounter = cosf(counter);	// cos counter

		display.UpdateWindowSize();	// 화면 갱신
		camera.Update(camera.GetPos(), 70.0f, display.GetWindowAspec(), 0.01F, 1000.0f);

		// TwSimple 배경추가
		display.Clear(scene.BgColor0[0], scene.BgColor0[1], scene.BgColor0[2], 1);	// 배경 초기화	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_world_coordinates.Draw();
		dMap.DrawPlane();

		///
		float delim = 2.0;

		// Rotate model	// TwSimple Rotation 추가
		scene.dt = glfwGetTime() - scene.time;
		if (scene.dt < 0) scene.dt = 0;
		scene.time += scene.dt;
		scene.turn += scene.speed*scene.dt;

		//// Rotate scene
		//if (scene.Rotation == Scene::ROT_CW)
		//	scene.RotYAngle -= 5.0*scene.dt;
		//else if (scene.Rotation == Scene::ROT_CCW)
		//	scene.RotYAngle += 5.0*scene.dt;


		// 도형 사각형
		shader1.Bind();
		texture1.Bind(0);

		transform1.SetPos(glm::vec3(0, 0, 0));
		transform1.SetPos(glm::vec3(1.1, 1.1, 0));

		transform1.GetPos().y += delim * sinf(scene.turn);
		transform1.GetPos().x += delim * cosf(scene.turn);
		transform1.GetRot().y = scene.turn * 0.5f;
		transform1.GetRot().x = scene.turn * 0.3f;

		shader1.Update(transform1, camera);
		mesh1.Draw();


		//coor_model_1.Draw();
	

		// Move lights
		scene.Update(scene.time);

		Transform sceneT;
		shader1.Bind();
		texture1.Bind(0);
		shader1.Update(sceneT, camera);

		// Draw Light UI 
		scene.Draw();

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		// Draw tweak bar UI
		TwDraw();

		display.Update();	// 화면갱신
		counter += 0.05f;	// 카운터 증가
	}

}

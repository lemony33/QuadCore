#include "Graphics_Simulator.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Controls.h"
#include "DrawMap.h"
//#include "RayCast.h"

QuadCore::Graphics_Simulator::Graphics_Simulator()
	: display(width_window, height_window, "Graphics Simulator - QuadCore")
{
}

QuadCore::Graphics_Simulator::~Graphics_Simulator()
{
}

void QuadCore::Graphics_Simulator::Run()
{
	// Cube_1
	Mesh mesh1("../media/shape/Cube.obj");
	Shader shader1("../media/new_shader/basicShader_tex");
	Texture texture1("../media/res/bricks.jpg");
	Transform transform1;

	// Cube_2
	Mesh mesh2("../media/shape/Cube.obj");
	Shader shader2("../media/new_shader/basicShader_tex");
	Texture texture2("../media/skyblue.jpg");
	Transform transform2;

	// World
	Transform worldCoordinate;

	float aspec = (float)width_window / (float)height_window;
	Camera camera(glm::vec3(0.0f, 0.0f, 10.0f), 70.0f, aspec, 0.01f, 1000.0f);

	Controls controls(display.GetWindow());
	Controls controller(controls, camera, worldCoordinate);

	DrawMap dMap(camera);
	dMap.SetProperty(100, 1.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

	//RayCast ray(controller);

	// ********************************************************************************************************
	while (!display.IsClosed())
	{
		// Window Set
		display.UpdateWindowSize();
		camera.Update(camera.GetPos(), 70.0f, display.GetWindowAspec(), 0.01f, 1000.0f);
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		// 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式 //
		// Draw Plane
		dMap.DrawPlane();

		// Draw Cube_1
		shader1.Bind();
		texture1.Bind(0);
		transform1.SetPos(glm::vec3(0.0f, 0.5f, 0.0f));
		shader1.Update(transform1, camera);
		mesh1.Draw();

		// Draw Cube_2
		//shader2.Bind();
		//texture2.Bind(0);
		transform2.SetPos(glm::vec3(1.0f, 0.5f, 0.0f));
		shader2.Update(transform2, camera);
		mesh2.Draw();

		// Raycast Testing ...
		//ray.GetRayValue();

		// 式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式 //

		// Window Update
		display.Update();
	}
	// ********************************************************************************************************
}

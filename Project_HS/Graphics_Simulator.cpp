#include "Graphics_Simulator.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "DrawMap.h"
#include "Controls.h"

typedef unsigned int UINT;

QuadCore::Graphics_Simulator::Graphics_Simulator()
	: display(width_window, height_window, "Graphics Simulator - QuadCore")
{
}
QuadCore::Graphics_Simulator::~Graphics_Simulator()
{
}
void QuadCore::Graphics_Simulator::Run()
{
	// Cube
	Mesh mesh_cube("../media/shape/Cube.obj");
	Shader shader_cube("../media/basicShader_ray");
	Texture texture_cube("../media/Pexel.jpeg");
	Transform transform_cube;

	// CubeHollow
	Mesh mesh_cubehollow("../media/shape/CubeHollow.obj");
	Shader shader_cubehollow("../media/basicShader_ray");
	Texture texture_cubehollow("../media/Pexel.jpeg");
	Transform transform_cubehollow;

	float aspec = (float)width_window / (float)height_window;
	Camera camera(glm::vec3(0, 0, 10), 70.0f, aspec, 0.01F, 1000.0f);

	// Plane
	DrawMap dMap(camera);
	dMap.SetProperty(10, 1.0f, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

	// Controller
	Controls controls(display.GetWindow());
	Controls controller(controls, camera, display);

	int i = 0;
	while (!display.IsClosed())
	{
		// Window
		display.UpdateWindowSize();
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		// Draw Map
		dMap.DrawPlane();

		// Cube
		shader_cube.Bind();
		texture_cube.Bind(0);
		transform_cube.SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
		if (dMap.GetPosition(glm::vec3(0.0f, 0.0f, 0.0f)) == 0)
			dMap.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f), 1);
		shader_cube.Update(transform_cube, camera);
		mesh_cube.Draw();

		// CubeHollow
		shader_cubehollow.Bind();
		texture_cubehollow.Bind(1);
		transform_cubehollow.SetPos(glm::vec3(2.0f, 0.0f, 0.0f));
		if (dMap.GetPosition(glm::vec3(2.0f, 0.0f, 0.0f)) == 0)
			dMap.SetPosition(glm::vec3(2.0f, 0.0f, 0.0f), 1);
		shader_cubehollow.Update(transform_cubehollow, camera);
		mesh_cubehollow.Draw();

		// Print Array
		if (i++ == 0)
			dMap.PrintArray();

		// Update
		display.Update();
	}
}

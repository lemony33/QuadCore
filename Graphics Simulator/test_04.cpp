#include "Graphics_Simulator.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

#include "Controls.h"


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
	Mesh mesh1("../media/shape/Wedge.obj");
	Mesh mesh2("../media/shape/CubeHollow.obj");

	// 2. Shader
	Shader shader1("../media/basicShader_light");
	Shader shader2("../media/basicShader_tex");

	//3. Texture
	Texture texture1("../media/res/bricks.jpg");
	Texture texture2("../media/skyblue.jpg");

	//4. Transform
	Transform worldCoordinate;
	Transform transform1;
	Transform transform2;
	float counter = 0.0f;

	//5. Camera
	float aspec = (float)width_window / (float)height_window;
	Camera camera(glm::vec3(0, 0, 10), 70.0f, aspec, 0.01F, 1000.0f);

	// Controls (Mouse / Keyboard)
	Controls controls(display.GetWindow());
	Controls controller(controls, camera, transform1);



	while (!display.IsClosed())
	{
		display.UpdateWindowSize();
		camera.Update(glm::vec3(0, 0, 5), 70.0f, display.GetWindowAspec(), 0.01F, 1000.0f);


		//display πŸ≈¡»≠∏È
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform1.GetPos().x = sinf(counter);
		transform1.GetPos().y = sinf(counter);	//
		transform1.GetPos().z = cosf(counter);
		transform1.GetRot().x = counter * 0.5;
		transform1.GetRot().y = counter * 0.5;
		transform1.GetRot().z = counter * 0.5;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		//transform2.GetPos().x = sinf(counter);
		transform2.GetPos().y = sinf(counter);	//
												//transform2.GetPos().z = cosf(counter);

		shader1.Bind();
		texture1.Bind(0);
		transform1.GetPos().x -= 2.5;
		transform1.SetScale(glm::vec3(1, 1, 1));
		shader1.Update(transform1, camera);
		mesh1.Draw();

		shader2.Bind();
		texture2.Bind(0);
		//transform.GetPos().x += 1.5;
		transform2.GetPos().y += 2.5;
		shader1.Update(transform2, camera);
		mesh2.Draw();

		display.Update();
		counter += 0.05f;
	}
}

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
	Shader shader1("../media/new_shader/basicShader_light");
	Shader shader2("../media/new_shader/basicShader_tex");
	
	//3. Texture
	Texture texture1("../media/res/bricks.jpg");
	Texture texture2("../media/skyblue.jpg");
	//texture2.Reset();
	

	//4. Transform
	Transform worldCoordinate;
	Transform transform1;
	Transform transform2;
	Transform transform3;
	
	
	//5. Camera
	float aspec = (float)width_window / (float)height_window;
	Camera camera(glm::vec3(0, 0, 10), 70.0f, aspec, 0.01F, 1000.0f);

	// Controls (Mouse / Keyboard)
	Controls controls(display.GetWindow());
	Controls controller(controls, camera, worldCoordinate);

	

	float counter = 0.0f;

	while (!display.IsClosed())
	{	
		float sinCounter = sinf(counter);	// sin counter
		float cosCounter = cosf(counter);	// cos counter

		display.UpdateWindowSize();	// 화면 갱신
		camera.Update(camera.GetPos(), 70.0f, display.GetWindowAspec(), 0.01F, 1000.0f);
				
		display.Clear(0.1f, 0.1f, 0.1f, 1.0f);	// 배경 초기화
		//display.Clear(1.0f, 1.0f, 1.0f, 1.0f);	// 배경 초기화

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		// Draw here
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		m_shape_manager;



		shader1.Bind();		
		texture1.Bind(1);
		//Texture::Reset();

		transform1.SetPos(glm::vec3(0, 0, 0));
		transform1.SetPos(glm::vec3(1.1, 1.1, 0));
		transform1.GetRot().y = counter * 0.5f;
		transform1.GetRot().x = counter * 0.3f;
		shader1.Update(transform1, camera);		
		mesh1.Draw();


		transform2.SetPos(glm::vec3(-1.1, 0, 0));

		transform2.GetRot().y = counter * 0.5f;
		transform2.GetRot().x = counter * 0.3f;
		shader1.Update(transform2, camera);
		mesh1.Draw();

		/*
		transform2.SetPos(glm::vec3(-1.1, 0, 0));
		shader1.Update(transform2, camera);
		mesh1.Draw();

		transform3.SetPos(glm::vec3(1.1, 0, 0));
		shader1.Update(transform3, camera);
		mesh1.Draw();



		transform1.SetPos(glm::vec3(0, 1.1, 0));
		shader1.Update(transform1, camera);
		mesh1.Draw();

		transform2.SetPos(glm::vec3(-1.1, 1.1, 0));
		shader1.Update(transform2, camera);
		mesh1.Draw();

		transform3.SetPos(glm::vec3(1.1, 1.1, 0));
		shader1.Update(transform3, camera);
		mesh1.Draw();


		transform1.SetPos(glm::vec3(0, -1.1, 0));
		shader1.Update(transform1, camera);
		mesh1.Draw();

		transform2.SetPos(glm::vec3(-1.1, -1.1, 0));
		shader1.Update(transform2, camera);
		mesh1.Draw();

		transform3.SetPos(glm::vec3(1.1, -1.1, 0));
		shader1.Update(transform3, camera);
		mesh1.Draw();
		*/

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		
		display.Update();	// 화면갱신
		counter += 0.05f;	// 카운터 증가
	}
}

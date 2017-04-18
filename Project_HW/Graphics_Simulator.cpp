#include "Graphics_Simulator.h"


#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

enum
{
	OBJECTSHADER,

	LIGHTSHADER,

	LAMPSHADER
};
enum
{
	DRAWELEMENTS,
	DRAWARRAYS

};


QuadCore::Graphics_Simulator::Graphics_Simulator()
	: display(width_window, height_window, "Graphics Simulator - QuadCore")
{
}


QuadCore::Graphics_Simulator::~Graphics_Simulator()
{
}


void QuadCore::Graphics_Simulator::Run()
{
	//Display display(width_window, height_window, "Graphics Simulator - QuadCore");
	//2. mesh 삼각형 도형그려주기
	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0,0.0)),
		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5,1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0,0.0)) };

	unsigned int indices[] = { 0,1,2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

		
	Mesh mesh2("../media/shape/Wedge.obj");
	Mesh mesh3("../media/shape/CubeHollow.obj");

	//1. shader도형색깔
	Shader shader("../media/res/basicShader", OBJECTSHADER);
	Shader basiclightshader("../media/shaders/BasicLight/basiclight", LIGHTSHADER);
	Shader lampshader("../media/shaders/BasicLight/lamp", LAMPSHADER);
	//3. Texture
	Texture texture("../media/res/bricks.jpg");
	//4. Transform
	Transform transform;
	Transform transform1;
	Transform transform2;
	float counter = 0.0f;
	//5. Camera
	Camera camera(glm::vec3(0, 0, 10.0f) , 70.0f, (float)width_window / (float)height_window, 0.01F, 100.0f);

	GLfloat deltaTime = 0;
	GLfloat lastFrame = 0;
	//반복문 시작 ------------------------------------------------------------------------------------
	while (!display.IsClosed())
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//display 바탕화면
		display.Clear(0.1f, 0.1f, 0.1f, 1.0f);
		//glfwPollEvents();
		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform1.GetPos().x = sinf(counter * 0.2f);
		//transform1.GetRot().y = counter * 0.01;

		//transform.GetPos().x = sinf(counter * 0.1f);
		transform.GetPos().y = sinf(counter * 0.2f); sinf(counter * 0.1f);
		transform.GetPos().z = cosf(counter * 0.1f);
		//transform.GetRot().x = counter * 1;
		transform.GetRot().y = counter * 0.01;
		//transform.GetRot().z = counter * 1;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
		//transform1.GetPos() = glm::vec3(1.2f * sinCounter, 1.0f, 2.0f * cosCounter);
		transform2.GetPos().x = cosf(counter * 0.1f);
		

		basiclightshader.Bind();
		//texture.Bind(0);
		basiclightshader.Update(transform, camera, transform1);
		mesh3.Draw(DRAWELEMENTS);
		

		lampshader.Bind();
		lampshader.Update(transform, camera, glm::vec3(0));
		mesh2.Draw(DRAWELEMENTS);
		texture.Bind(0);

		

		display.Update();
		counter += 0.1f;
		//glfwSwapBuffers(display.GetWindow());
	}
}



#include <iostream>
//#include <GL/glew.h>
#include <GLEW-2.0.0_x64/GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	Display display(WIDTH, HEIGHT, "Hello QuadCore");
	
	//2. mesh 삼각형 도형그려주기
	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0,0.0)),
						  Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5,1.0)),
						  Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0,0.0)) };

	unsigned int indices[] = { 0,1,2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh mesh2("./res/numbers.obj");
	//1. shader도형색깔
	Shader shader("./res/basicShader");
	//3. Texture
	Texture texture("./res/bricks.jpg");
	//4. Transform
	Transform transform;
	float counter = 0.0f;
	//5. Camera
	Camera camera(glm::vec3(0, 0, -120), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01F, 1000.0f);

	while (!display.IsClosed())
	{
		//display 바탕화면
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform.GetPos().x = sinf(counter);
		transform.GetPos().z = cosf(counter);
		transform.GetRot().x = counter * 0.5;
		transform.GetRot().y = counter * 0.5;
		transform.GetRot().z = counter * 0.5;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh2.Draw();

		display.Update();
		counter += 0.1f;
	}

	return 0;
}
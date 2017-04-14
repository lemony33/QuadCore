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
	Display display(WIDTH, HEIGHT, "Hello QuadCore"); // 1. display
	
	Vertex vertices[] = { Vertex(glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec2(0.0,0.0)), //3.  vec3: 삼각형 도형그려주기 => vec2: texture
							Vertex(glm::vec3(-0.25f,  0.25f, -0.25f), glm::vec2(0.0,1.0)),
							Vertex(glm::vec3(0.25f, -0.25f, -0.25f), glm::vec2(1.0,1.0)),
							Vertex(glm::vec3(0.25f,  0.25f, -0.25f), glm::vec2(0.0,1.0)),
							Vertex(glm::vec3(0.25f, -0.25f,  0.25f), glm::vec2(0.0,1.0)) ,
							Vertex(glm::vec3(0.25f,  0.25f,  0.25f), glm::vec2(0.0,1.0)) ,
							Vertex(glm::vec3(-0.25f, -0.25f,  0.25f), glm::vec2(0.0,1.0)) ,
							Vertex(glm::vec3(-0.25f,  0.25f,  0.25f), glm::vec2(0.0,1.0)) };

	unsigned int indices[] = { 0, 1, 2, // back 
		2, 1, 3,
		2, 3, 4, // right
		4, 3, 5,
		4, 5, 6, // front
		6, 5, 7,
		6, 7, 0, // left
		0, 7, 1,
		6, 0, 2, // bottom
		2, 4, 6,
		7, 5, 3, // top
		7, 3, 1 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0])); // vertex이용해서 삼각형 그려줄때
	//Mesh mesh2("./res/monkey3.obj");	
	//Mesh mesh3("./res/numbers.obj");
	
	Shader shader("./res/basicShader");  //2. vs, fs shader : 도형색깔
	
	Texture texture("./res/bricks.jpg"); //4. Texture
	
	Transform transform;				 //5. Transform
	float counter = 0.0f;
	
	Camera camera(glm::vec3(0, 0, 3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01F, 1000.0f); //6. Camera

	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f); //display 바탕화면

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
		mesh.Draw();
		//mesh2.Draw();
		//mesh3.Draw();

		display.Update();
		counter += 0.1f;
	}

	return 0;
}
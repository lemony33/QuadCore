/*
OpenGL 4.5 - 2014
GLFW 3.2.1 - Released on August 18, 2016
GLEW 2.0.0 - Rleased on 24 Jul 2016
GLM 0.9.8.4 - Rleased on 22 Jan 2017
 
 # 주의: glew32.dll 파일을 추가필요
*/


//#pragma comment(lib, "glu32.lib")
#include <GLEW-2.0.0_x64/GL/glew.h>
//#include <GLFW/glfw3.h>
#include <GL\GLU.h>						// window system
#include <cstring>
#include <stdlib.h>			// srand, rand
#include <thread>			// std::this_thread::sleep_for
#include <chrono>			// std::chrono::seconds
#include <iostream>
#include "math.h"
#include <vector>
#include "Matrix4.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Vector3.h"
#include "ObjReader.h"


#include "Display.h"

#include "camera.h"
#include "Mesh.h"
#include "transform.h"
#include "shader.h"
#include "texture.h"


const int width_window = 640;
const int height_window = 640;


std::string readFromTxt(const char* filename)
{
	using namespace std;

	ifstream inFile;
	inFile.open(filename);	// open the input file

	stringstream strStream;
	strStream << inFile.rdbuf();	// read the file
	string str = strStream.str();	// str holds the content of

	return str;
}


int main(int argc, char** argv)
{
	Display display(width_window, height_window, "Graphics Simulator - QuadCore");

	//2. mesh 삼각형 도형그려주기
	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0,0.0)),
		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5,1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0,0.0)) };

	unsigned int indices[] = { 0,1,2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	//Mesh mesh2("./object/magnolia.obj");
	Mesh mesh2("./object/cube.obj");
	//1. shader도형색깔
	Shader shader("./res/basicShader");
	//3. Texture
	Texture texture("./res/bricks.jpg");
	//4. Transform
	Transform transform;
	float counter = 0.0f;
	//5. Camera
	Camera camera(glm::vec3(0, 0, -20), 70.0f, (float)width_window / (float)height_window, 0.01F, 1000.0f);

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
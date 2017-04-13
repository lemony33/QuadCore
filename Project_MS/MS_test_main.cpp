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


int main(void)
{
	Display display(width_window, height_window, "Hello World!");


	int width, height;
	//glfwGetFramebufferSize(window, &width, &height);
	display.GetFrameBufferSize(&width, &height);
	glViewport(0, 0, width, height);
	glOrtho(-2.2, 2.2, -2.2, 2.2, -100.0, 100.0);
	gluLookAt(1.0, 1.0, 1.0, 0.5, 0.5, 0.5, 0, 1, 0);

	// read 3D model from obj file

	//std::string obj_name = "airboat.obj";
	std::string obj_name = "cube.obj";
	//std::string obj_name = "diamond.obj";
	//std::string obj_name = "lamp.obj";
	//std::string obj_name = "magnolia.obj";
	//std::string obj_name = "skyscraper.obj";
	//std::string obj_name = "test.obj";
	//std::string obj_name = "IronMan_Full_smooth.obj";
	//std::string obj_name = "torus.obj";
	obj_name = "object/" + obj_name;
	
	OBJReader obj_reader;
	obj_reader.readObj(obj_name.c_str());
	//obj_reader.readObj("test.obj");
	//obj_reader.dump();
	obj_reader.scaleToUnitBox();
	
	const std::vector < Vector3<float> > &vertices = obj_reader.pos_stack_;
	const std::vector < Vector3<unsigned int> > &indices = obj_reader.ix_stack_;

	// copy geometry to buffer object
	GLuint vbo[3];
	glGenBuffers(3, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3<float>) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3<float>) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vector3<unsigned int>) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* *** SET SHADER START *** */
	const std::string vertex_shader = readFromTxt("vertex_shader_5_4.glsl");
	const std::string fragment_shader = readFromTxt("fragment_shader_5_4.glsl");
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	char const * vertex_source_point = vertex_shader.c_str();
	char const * fragment_source_point = fragment_shader.c_str();
	/* *** SET SHADER END *** */

	glShaderSource(vs, 1, &vertex_source_point, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_source_point, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glBindAttribLocation(shader_programme, 0, "a_pos");
	glLinkProgram(shader_programme);

	// Check the link status
	GLint linked = 0;
	glGetProgramiv(shader_programme, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(shader_programme, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char)*infoLen);

			glGetProgramInfoLog(shader_programme, infoLen, NULL, infoLog);
			printf("Error linking program:\n%s\n", infoLog);

			free(infoLog);
		}

		system("pause");

		glDeleteProgram(shader_programme);
		return false;
	}

	/* *** SHADER *** */

	/* Loop until the user closes the window */
	while (!display.IsClosed())
	{
		//display 바탕화면
		//display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		/* Render here */


		//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		//glEnableClientState(GL_VERTEX_ARRAY);
		//glColorPointer(3, GL_FLOAT, 0, 0);			// Vector3

		//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		//glEnableClientState(GL_COLOR_ARRAY);
		//glVertexPointer(3, GL_FLOAT, 0, 0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		//glPolygonMode(GL_FRONT, GL_FILL);
		//glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, 0);

		//glDisableClientState(GL_COLOR_ARRAY);
		//glDisableClientState(GL_VERTEX_ARRAY);


		/* *** USE SHADER START *** */

		// shader version
		glUseProgram(shader_programme);	// activate your shader!


		GLint loc = glGetUniformLocation(shader_programme, "Scale");
		if (loc != -1)
		{
			static float scale = 0.0;
			scale += 0.3f;

			glUniform1f(loc, sin(scale));
		}

		// draw here
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer
		(
			0,				// attribute 0. No particular reason for 0, but mu
			3,				// size (x,y,z)
			GL_FLOAT,		// type
			GL_FALSE,		// normalized?
			0,				// stride
			(void*)0		// array buffer offset
		);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, 0);


		/* *** USE SHADER END *** */

		display.Update();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}

	return 0;
}
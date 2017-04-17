#include <iostream>
//#include <GL/glew.h>
#include <GLEW-2.0.0_x64/GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

//#include "sb7.h"
//#include "../include/shader.h"
//#include "object.h"
//#include "sb7ktx.h"


#define WIDTH 800
#define HEIGHT 600


#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>



int main(int argc, char** argv)
{
	Display display(WIDTH, HEIGHT, "Hello QuadCore"); // 1. display
	
	//envmaps[0] = sb7::ktx::file::load("../media/textures/envmaps/mountaincube.ktx");
	//tex_envmap = envmaps[envmap_index];

	Vertex vertices[] = { Vertex(glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec2(0.0,0.0)), //3.  vec3: 삼각형 도형그려주기 => vec2: texture
							Vertex(glm::vec3(-0.25f,  0.25f, -0.25f), glm::vec2(0.0,1.0)),
							Vertex(glm::vec3(0.25f, -0.25f, -0.25f), glm::vec2(1.0,1.0)),
							Vertex(glm::vec3(0.25f,  0.25f, -0.25f), glm::vec2(1.0,1.0)),
							Vertex(glm::vec3(0.25f, -0.25f,  0.25f), glm::vec2(1.0,1.0)) ,
							Vertex(glm::vec3(0.25f,  0.25f,  0.25f), glm::vec2(1.0,1.0)) ,
							Vertex(glm::vec3(-0.25f, -0.25f,  0.25f), glm::vec2(1.0,1.0)) ,
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
	Mesh mesh2("../media/shape/CubeHollow.obj");	
	//Mesh mesh3("./res/numbers.obj");
	
	//Shader shader("./res/basicShader");  //2. vs, fs shader : 도형색깔
	//Shader shader("./res/basicShader_gold");  //2. vs, fs shader : 도형색깔
	Shader shader("./res/basicShader_phong");  //2. vs, fs shader : 도형색깔
	
	Texture texture("./res/bricks.jpg"); //4. Texture
	
	Transform transform;				 //5. Transform
	float counter = 0.0f;
	
	//Camera camera(glm::vec3(0.7, 0.8, 4.0), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01F, 1000.0f); //6. Camera
	Camera camera(glm::vec3(0.7, 0.3, 2.0), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01F, 1000.0f); //6. Camera




	Shader lightingShader("./res/shaders/lighting.vs", "./res/shaders/lighting.frag");
	Shader lampShader("./res/shaders/lamp.vs", "./res/shaders/lamp.frag");

	// First, set the container's VAO (and VBO)
	GLuint VBO, containerVAO;
	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(containerVAO);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0); // Note that we skip over the normal vectors
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);



	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f); //display 바탕화면

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		//transform.GetPos().x = sinf(counter);      
		//transform.GetPos().y = sinf(counter);
		//transform.GetPos().z = cosf(counter);
		//transform.GetRot().x = counter * 0.5;
		transform.GetRot().y = counter * 0.5;
		//transform.GetRot().z = counter * 0.5;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//glEnable(GL_TEXTURE_CUBE_MAP);

		//glBindTexture(GL_TEXTURE_CUBE_MAP, tex_envmap);

		//*******************************************************************************************

		// Light attributes
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

		///

		lightingShader.Use();
		GLint objectColorLoc = glGetUniformLocation(lightingShader.Program, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(lightingShader.Program, "lightColor");
		GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "lightPos");
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
		glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y*counter*30, camera.GetPosition().z);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");


		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.GetViewProjection()));


		// Draw the container (using container's vertex attributes)
		glBindVertexArray(containerVAO);
		glm::mat4 model;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.GetViewProjection()));
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		//*******************************************************************************************
		
		//shader.Bind();
		//texture.Bind(0);
		//lightingShader.Update(transform, camera);
		mesh2.Draw();
		//mesh2.Draw();
		//mesh3.Draw();

		display.Update();
		//counter += 0.001f;
		counter += 5.0f;
	}

	return 0;
}
#include "Graphics_Simulator.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"



QuadCore::Graphics_Simulator::Graphics_Simulator()
	: display(width_window, height_window, "Graphics Simulator - QuadCore")
{
}


QuadCore::Graphics_Simulator::~Graphics_Simulator()
{
}


void QuadCore::Graphics_Simulator::Run()
{
	//// mesh �ﰢ�� �����׷��ֱ�
	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5, -0.5, 0.0),	glm::vec2(0.0,0.0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(+0.5, -0.5, 0.0),	glm::vec2(1.0,0.0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(+0.5, +0.5, 0.0),	glm::vec2(1.0,1.0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-0.5, +0.5, 0.0),	glm::vec2(0.0,1.0), glm::vec3(0, 0, 1)),
	};
	unsigned int indices[] = {
		0,1,2,
		2,3,0,
	};
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	// *.obj ���Ϸε�

	Mesh mesh1("../media/shape/Wedge.obj");
	Mesh mesh2("../media/shape/CubeHollow.obj");
	//1. shader��������	
	//Shader shader("../media/MakePlaneShader");
	//Shader shader("../media/res/basicShader");
	Shader shader("../media/basicShader_light");
	Shader shader2("../media/basicShader_tex");
	//3. Texture
	Texture texture("../media/res/bricks.jpg");
	Texture texture2("../media/skyblue.jpg");
	//4. Transform
	Transform transform;
	float counter = 0.0f;
	//5. Camera
	Camera camera(glm::vec3(0, 0, 5), 70.0f, (float)width_window / (float)height_window, 0.01F, 1000.0f);

	while (!display.IsClosed())
	{
		//display ����ȭ��
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform.GetPos().x = sinf(counter);
		transform.GetPos().y = sinf(counter);	//
		transform.GetPos().z = cosf(counter);
		transform.GetRot().x = counter * 0.5;
		transform.GetRot().y = counter * 0.5;
		transform.GetRot().z = counter * 0.5;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		transform.GetPos().x -= 2.5;
		transform.SetScale(glm::vec3(1, 1, 1));
		shader.Update(transform, camera);
		///mesh1.Draw();

		shader2.Bind();
		texture2.Bind(0);
		//transform.GetPos().x += 1.5;
		transform.GetPos().y += 0.5;
		//transform.GetPos().z += 1.5;
		transform.SetScale(glm::vec3(3, 0.5, 1));
		shader.Update(transform, camera);
		///mesh2.Draw();


		//shader.Bind();
		//texture.Bind(0);
		//transform.SetScale(glm::vec3(1, 1, 1));
		//transform.GetPos().y -= 10.0;

		shader.Bind();
		texture.Bind(0);
		transform.GetPos().x += 2.5;
		transform.SetScale(glm::vec3(1, 1, 1));
		shader.Update(transform, camera);

		//mesh.Draw();	


		////////////////////////////////////////////////////////////////////


		Shader shader_UI = ("../media/new_shader/basicShader_2D_HUD");
		Texture texture1("../media/res/bricks.jpg");

		shader_UI.Bind();
		texture1.Bind(0);

		Transform transform_UI;
		//transform_UI.GetPos().x = 1;
		//transform_UI.GetPos().y = 1;
		//transform_UI.GetPos().x += 1.0f;
		//transform_UI.GetPos().y += 1.0f;

		transform_UI.GetRot().x = counter * 0.05;
		transform_UI.GetRot().y = counter * 0.05;

		//glDisable(GL_DEPTH_TEST);
		shader_UI.Update(transform_UI, camera);
		mesh.Draw();
		//glEnable(GL_DEPTH_TEST);


		////////////////////////////////////////////////////////////////////

		display.Update();
		counter += 0.05f;
	}
}

/*
GitHub Wiki ����
https://github.com/antaehyeon/Hyeon-Schedule/wiki

OpenGL ���� ���̺귯�� ����
GL/GLES/EGL/GLX/WGL


OpenGL - 1.0 ���� �׸���
glBegin( GL_QUADS )
glVertex2f(  10, 10 );
glVertex2f(  10, -10 );
glVertex2f( -10, -10 );
glVertex2f( -10, 10 );
glEnd()

OpenGL - 2.0 ���� �׸���
float points[] = {
10, 10,
10, -10,
-10, -10,
-10, 10
};
glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, points);
glEnableVertexAttribArray(0);
glDrawArrays( GL_QUADS, 0, 4 );
*/
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
	//// mesh 삼각형 도형그려주기
	Vertex vertices[] = {
							Vertex(	glm::vec3(-0.5, -0.5,  0.0),	glm::vec2(0.0,0.0)	),
							Vertex(	glm::vec3( 0.0,  0.5,  0.0),	glm::vec2(0.0,1.0)	),
							Vertex(	glm::vec3( 0.5, -0.5,  0.0),	glm::vec2(1.0,1.0)	),
							Vertex(	glm::vec3( 0.0, -1.5,  0.0),	glm::vec2(0.0,1.0)	),
						};
	unsigned int indices[] = {
								2,1,0,
								3,2,0,
							};
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	// *.obj 파일로딩

	Mesh mesh1("../media/shape/Wedge.obj");
	Mesh mesh2("../media/shape/CubeHollow.obj");
	//1. shader도형색깔	
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
		//display 바탕화면
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
		mesh1.Draw();

		//shader2.Bind();
		//texture2.Bind(0);
		////transform.GetPos().x += 1.5;
		//transform.GetPos().y += 0.5;
		////transform.GetPos().z += 1.5;
		//transform.SetScale(glm::vec3(3,0.5,1));
		//shader.Update(transform, camera);		
		//mesh2.Draw();


		//shader.Bind();
		//texture.Bind(0);
		//transform.SetScale(glm::vec3(1, 1, 1));
		//transform.GetPos().y -= 10.0;

		shader.Bind();
		texture.Bind(0);
		transform.GetPos().x += 2.5;
		transform.SetScale(glm::vec3(1, 1, 1));
		shader.Update(transform, camera);

		
		//GLUquadric *sphere; // object 선언
		//sphere = gluNewQuadric(); // object 생성
		//gluSphere(sphere, 0.3f, 50, 10);  // sphere 그리기
		
		GLUquadric *cylinder;
		cylinder = gluNewQuadric();
		gluCylinder(cylinder, 0.8f, 0.3f, 1, 50, 10);
		
		

		// opengl - 1버전 방식
		//glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
			glVertex3f(-5, 3, 0);			
			glVertex3f(+5, 3, 0);
		glEnd();

		transform.GetPos().x = 0;
		shader.Update(transform, camera);
		glLineWidth(10.0);
		glColor3f(1.f, 0.f, 0.f);		// 빨간색 지정
		glBegin(GL_LINE_LOOP);			// x축 그리기
		glVertex3f(1.0, 0.0, 0.0);		// 시작 점
		glVertex3f(-1.0, 0.0, 0.0);		// 끝 점
		glEnd();

		glColor3f(0.f, 1.f, 0.f);		// 초록색 지정
		glBegin(GL_LINE_LOOP);			// y축 그리기
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, -1.0, 0.0);
		glEnd();
		glColor3f(0.f, 0.f, 1.f);		// 파란색 지정
		glBegin(GL_LINE_LOOP);			// z축 그리기
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, -1.0);
		glEnd();

		//GLfloat vertices[][3] = {
		//							{ -1.0,-1.0,-1.0 },	// 0
		//							{ 1.0,-1.0,-1.0 },	// 1
		//							{ 1.0,1.0,-1.0 },	// 2
		//							{ -1.0,1.0,-1.0 },	// 3
		//							{ -1.0,-1.0,1.0 },
		//							{ 1.0,-1.0,1.0 },
		//							{ 1.0,1.0,1.0 },
		//							{ -1.0,1.0,1.0 }
		//						};
		//
		//glBegin(GL_QUADS);
		//glVertex3fv(vertices[0]);
		//glVertex3fv(vertices[1]);
		//glVertex3fv(vertices[2]);
		//glVertex3fv(vertices[3]);
		//glEnd();

		//// opengl - 2버전 방식
			

		//float points[] = {
		//	-10, 10,
		//	-10, 5,
		//	-5, 5,
		//	-5, 10
		//};
		//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, points);
		//glEnableVertexAttribArray(0);
		//glDrawArrays(GL_QUADS, 0, 4);

		float quadVertices[] = {
			-1.0,-1.0, 0.0, 
			1.0,-1.0, 0.0, 
			1.0,1.0, 0.0,
			-1.0,1.0, 0.0,
		};

		//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, quadVertices);		
		//glEnableVertexAttribArray(0);

		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//glVertexPointer(3, GL_FLOAT, 0, quadVertices);
		//glDrawArrays(GL_QUADS, 0, 4);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glEnableVertexAttribArray(0);
		

		display.Update();
		counter += 0.05f;
	}
}

/*
GitHub Wiki 예시
https://github.com/antaehyeon/Hyeon-Schedule/wiki

OpenGL 보조 라이브러리 종류
GL/GLES/EGL/GLX/WGL


OpenGL - 1.0 버전 그리기
glBegin( GL_QUADS )
glVertex2f(  10, 10 );
glVertex2f(  10, -10 );
glVertex2f( -10, -10 );
glVertex2f( -10, 10 );
glEnd()

OpenGL - 2.0 버전 그리기
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
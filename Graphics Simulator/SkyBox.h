#pragma once

#include "iShape.h"

class SkyBox : public QuadCore::iShape
{
public:
	SkyBox(std::string img_name)
	{
		skyboxShader = new Shader("../resources/shaders/cubemaps/skybox"/*img_name*/);
		skyboxMesh = new Mesh(SkyBoxVerties, sizeof(SkyBoxVerties) / sizeof(SkyBoxVerties[0]), indices, sizeof(indices) / sizeof(indices[0]));

		faces.push_back("../resources/textures/cubemaps/" + img_name + "/right.jpg");
		faces.push_back("../resources/textures/cubemaps/" + img_name + "/left.jpg");
		faces.push_back("../resources/textures/cubemaps/" + img_name + "/top.jpg");
		faces.push_back("../resources/textures/cubemaps/" + img_name + "/bottom.jpg");
		faces.push_back("../resources/textures/cubemaps/" + img_name + "/back.jpg");
		faces.push_back("../resources/textures/cubemaps/" + img_name + "/front.jpg");
		
		skyboxTexture = new QuadCore::Texture(faces);
	}

public:
	virtual void Draw(QuadCore::Camera* camera, bool enable_coor)
	{
		glDepthFunc(GL_LEQUAL);
		skyboxShader->Bind();
		skyboxTexture->Bind(0);
		skyboxMesh->Draw();
		skyboxShader->Update(transform, *camera);
		glDepthFunc(GL_LESS);
	}

private:	
	QuadCore::Transform transform;

	Mesh* skyboxMesh;
	Shader* skyboxShader;
	QuadCore::Texture* skyboxTexture;

	std::vector<std::string> faces;		//스카이박스 텍스쳐 들어가는 부분

	float skybox_size = 300.0f;
	Vertex SkyBoxVerties[24] = // 스카이박스 vertices
	{
		// back
		Vertex(glm::vec3(-skybox_size, -skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),	// 0
		Vertex(glm::vec3(+skybox_size, -skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),	// 1
		Vertex(glm::vec3(+skybox_size, +skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),	// 2
		Vertex(glm::vec3(-skybox_size, +skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, -1.0f)),	// 3

		// front
		Vertex(glm::vec3(-skybox_size, -skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, +1.0f)),	// 4
		Vertex(glm::vec3(+skybox_size, -skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, +1.0f)),	// 5
		Vertex(glm::vec3(+skybox_size, +skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, +1.0f)),	// 6
		Vertex(glm::vec3(-skybox_size, +skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  0.0f, +1.0f)),	// 7

		// left
		Vertex(glm::vec3(-skybox_size, -skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f, 0.0f)),	// 4 - 8
		Vertex(glm::vec3(-skybox_size, -skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f, 0.0f)),	// 0 - 9
		Vertex(glm::vec3(-skybox_size, +skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f, 0.0f)),	// 3 - 10
		Vertex(glm::vec3(-skybox_size, +skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(-1.0f,  0.0f, 0.0f)),	// 7 - 11

		// right
		Vertex(glm::vec3(+skybox_size, -skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(+1.0f,  0.0f, 0.0f)),	// 5 - 12
		Vertex(glm::vec3(+skybox_size, -skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(+1.0f,  0.0f, 0.0f)),	// 1 - 13
		Vertex(glm::vec3(+skybox_size, +skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(+1.0f,  0.0f, 0.0f)),	// 2 - 14
		Vertex(glm::vec3(+skybox_size, +skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(+1.0f,  0.0f, 0.0f)),	// 6 - 15

		// top
		Vertex(glm::vec3(-skybox_size, +skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  +1.0f, 0.0f)),	// 3 - 16
		Vertex(glm::vec3(+skybox_size, +skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  +1.0f, 0.0f)),	// 2 - 17
		Vertex(glm::vec3(+skybox_size, +skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  +1.0f, 0.0f)),	// 6 - 18
		Vertex(glm::vec3(-skybox_size, +skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  +1.0f, 0.0f)),	// 7 - 19

		// bottom
		Vertex(glm::vec3(-skybox_size, -skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f, 0.0f)),	// 0 - 20
		Vertex(glm::vec3(+skybox_size, -skybox_size, -skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f, 0.0f)),	// 1 - 21
		Vertex(glm::vec3(+skybox_size, -skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f, 0.0f)),	// 5 - 22
		Vertex(glm::vec3(-skybox_size, -skybox_size, +skybox_size),glm::vec2(0,0),glm::vec3(0.0f,  -1.0f, 0.0f)),	// 4 - 23
	};
	unsigned int indices[48] = {
		 0, 1, 2,    2, 3, 0,		// back
		 5, 4, 7,    7, 6, 5,		// front
		 8, 9,10,   10,11, 8,		// left
		13,12,15,   15,14,13,		// right
		16,17,18,   18,19,16,		// top
		21,20,23,   23,22,21,		// bottom
	};
};


/*
//스카이박스 텍스쳐 들어가는 부분
std::vector<std::string> faces;
faces.push_back("../media/textures/skybox/right.jpg");
faces.push_back("../media/textures/skybox/left.jpg");
faces.push_back("../media/textures/skybox/top.jpg");
faces.push_back("../media/textures/skybox/bottom.jpg");
faces.push_back("../media/textures/skybox/back.jpg");
faces.push_back("../media/textures/skybox/front.jpg");

Texture skyboxTexture(faces);
*/


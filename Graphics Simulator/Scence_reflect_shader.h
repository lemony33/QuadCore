#pragma once


#include "iScene.h"


class Scence_reflect_shader : public QuadCore::iScene
{
public:

	Scence_reflect_shader()
	{
		Draw();
	}

	virtual ~Scence_reflect_shader()
	{
	}

public:
	virtual void Play()
	{
		
		m_shape_manager.DrawAll();
	}

private:
	//Mesh nanosuitMesh("../media/objects/nanosuit_reflection/nanosuit.obj");

	//Shader glassShader("../media/shaders/cubemaps/glass");
	//Shader mirrorShader("../media/shaders/cubemaps/mirror");

	//Transform glassTrans(glm::vec3(10.0, 0, 0));
	//Transform mirrorTrans(glm::vec3(-10.0, 0, 0));

	virtual void Draw()
	{
		
	}
};


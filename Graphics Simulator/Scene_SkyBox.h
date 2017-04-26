#pragma once


#include "iScene.h"
#include "SkyBox.h"


using QuadCore::Transform;

class Scene_SkyBox : public QuadCore::iScene
{
public:

	Scene_SkyBox()
	{
		Draw();
	}

	virtual ~Scene_SkyBox()
	{
	}

public:
	virtual void Play()
	{
		m_shape_manager.DrawAll();
	}

private:
	virtual void Draw()
	{
		using QuadCore::iShape;
		iShape* skybox_lake = new SkyBox("skybox");
		m_shape_manager.Insert_Object(skybox_lake);
	}
};


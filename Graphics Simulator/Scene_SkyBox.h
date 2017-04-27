#pragma once


#include "iScene.h"
#include "SkyBox.h"


using QuadCore::Transform;

class Scene_SkyBox : public QuadCore::iScene
{
public:

	Scene_SkyBox()
	{
	}

	virtual ~Scene_SkyBox()
	{
	}

public:
	virtual void Animate()
	{
	}

private:
	virtual void Draw()
	{
		using QuadCore::iShape;
		iShape* skybox_lake = new SkyBox("skybox");
		m_shape_manager.Insert_Object(skybox_lake);
	}
};


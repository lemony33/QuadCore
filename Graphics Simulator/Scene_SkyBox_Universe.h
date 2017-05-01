#pragma once


#include "iScene.h"
#include "SkyBox.h"


using QuadCore::Transform;

class Scene_SkyBox_Universe : public QuadCore::iScene
{
public:

	Scene_SkyBox_Universe()
	{
	}

	virtual ~Scene_SkyBox_Universe()
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
		iShape* skybox_universe = new SkyBox("milkyway");
		//iShape* skybox_lake = new SkyBox("milkyway");
		m_shape_manager.Insert_Object(skybox_universe);
	}
};


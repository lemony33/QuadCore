#pragma once

#include "iScene.h"


class Scene_main : public QuadCore::iScene
{
public:
	Scene_main()
	{
		Draw();
	}

	virtual ~Scene_main()
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
	}

};

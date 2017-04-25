#pragma once


#include "iScene.h"


class Scence_test_shader : public QuadCore::iScene
{
public:

	Scence_test_shader()
	{
		Draw();
	}

	virtual ~Scence_test_shader()
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


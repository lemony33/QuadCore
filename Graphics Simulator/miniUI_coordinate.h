#pragma once

#include "iShape.h"

namespace QuadCore
{

class miniUI_coordinate : public iShape
{
public:

	miniUI_coordinate()
	{
		m_transform = new Transform();
		m_coordinate = new Coordinates(1.0f);
		
		m_shader = new Shader("../resources/shaders/Final/basicShader_2D_HUD");
		m_texture = new Texture("../resources/textures/bricks.jpg");
	}

	virtual ~miniUI_coordinate()
	{
	}

public:
	virtual void Draw(QuadCore::Camera* camera, bool enable_coor)
	{
		m_shader->Bind();
		m_texture->Bind(0);

		m_transform->GetPos().x = +0.7f;
		m_transform->GetPos().y = -0.7f;

		m_transform->SetRot(camera->GetRot());

		m_shader->Update(*m_transform, *camera);

		if (enable_coor)
		{
			m_coordinate->Init_UI(m_transform, camera, 0.1f);
			m_coordinate->Draw(5.0f);
		}
	}
};

}
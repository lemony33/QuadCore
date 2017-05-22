#pragma once

#include "iShape.h"

namespace QuadCore
{

	class World_coordinate : public iShape
	{
	public:

		World_coordinate()
		{
			m_transform = new Transform();
			m_coordinate = new Coordinates(1.0f);
			
			m_shader = new Shader("../resources/shaders/Final/MapShader");
			m_texture = new Texture("../resources/textures/bricks.jpg");
		}

		virtual ~World_coordinate()
		{
		}

public:
	virtual void Draw(QuadCore::Camera* camera, bool enable_coor, bool poly_mode = false)
	{
		m_shader->Bind();
		m_texture->Bind(0);			
		m_shader->Update(*m_transform, *camera);

		if (enable_coor)
		{
			m_coordinate->Init(m_transform, camera, 50.0f);
			m_coordinate->Draw(3.0f);
		}
	}
};

}
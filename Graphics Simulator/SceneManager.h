#pragma once

#include "ShapeManager.h"
#include "iScene.h"

#include "DrawMap.h"

#include "Scene_main.h"
#include "Scence_moving_wall.h"
#include "Scence_moving_block.h"
#include "Scence_moving_cube.h"
#include "Scence_test_shader.h"


class SceneManager
{
public:
	SceneManager()
	{
		m_scene_list.push_back(new Scene_main);
		m_scene_list.push_back(new Scence_moving_wall);
		m_scene_list.push_back(new Scence_moving_block);
		m_scene_list.push_back(new Scence_moving_cube);
		m_scene_list.push_back(new Scence_test_shader);
	}

	virtual ~SceneManager()
	{
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// �ʿ��� ������ �ʱ�ȭ
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Init(QuadCore::Camera* camera)
	{
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

		dMap.Init(camera);
		dMap.SetProperty(100, 1.0f, glm::vec4(0.7f, 0.7f, 0.7f, 3.0f));		// Draw Map

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

		for (int i = 0; i < m_scene_list.size(); i++)
		{
			m_scene_list.at(i)->Init(camera);
		}
	}		

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	// ����� ����Ѵ�.
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	void Play()
	{		
		counter += 0.05f;
		QuadCore::iScene::SetCounter(counter);

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

		dMap.DrawPlane();		// Draw Map	
		
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

		for (int i = 0; i < m_scene_list.size(); i++)
		{
			m_scene_list.at(i)->Play();
		}
	}
	
private:
	float counter = 0.0f;

	std::vector<QuadCore::iScene*> m_scene_list;

	QuadCore::DrawMap dMap;
};


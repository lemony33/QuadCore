#pragma once

#include <chrono>			// timer
#include <iostream>
#include "ShapeManager.h"


class Scene
{
public:
	Scene()
	{
	}

	virtual ~Scene()
	{
	}

	void Init(QuadCore::Camera* camera)
	{
		m_shape_manager.Init(camera);
	}

	// ����� ����Ѵ�.
	void Play()
	{		
		counter += 0.05f;
		m_shape_manager.SetCounter(counter);
		//m_shape_manager.SetCounter(this->GetCounter_timer());



		m_shape_manager.DrawAll();	// ���� �׸���
	}


	// Timer ���, Ŭ���� ���� ������ �κ� (static���� ����ϴ� ���� ���� �� ����)
private:
	std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();	// ���۽ð�

	// ����ð��� ī���� ������ �޾ƿ´�
	float GetCounter_timer()
	{
		//auto start = std::chrono::high_resolution_clock::now();
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = end - start;
		auto i_millis = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
		auto f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(dur);
		//std::cout << i_millis.count() << '\n';
		std::cout << f_secs.count() << '\n';
		return f_secs.count();
	}


private:
	float counter = 0.0f;
	QuadCore::ShapeManager m_shape_manager;

};


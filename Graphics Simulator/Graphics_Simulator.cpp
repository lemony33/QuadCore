
#include "Graphics_Simulator.h"
#include <algorithm>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Controls.h"
#include "DrawMap.h"


QuadCore::Graphics_Simulator::Graphics_Simulator()
	: display(width_window, height_window, "Graphics Simulator - QuadCore")
{
}


QuadCore::Graphics_Simulator::~Graphics_Simulator()
{
}


void QuadCore::Graphics_Simulator::Run()
{
	//4. Transform
	Transform world_transform;
	///Transform UI_transform;

		
	//5. Camera
	float aspec = (float)width_window / (float)height_window;
	Camera camera(glm::vec3(0, 0, 10), 70.0f, aspec, 0.01F, 1000.0f);

	// Controls (Mouse / Keyboard)
	Controls controls(display.GetWindow());
	Controls controller(controls, camera, world_transform);

	///m_world_coordinates.Init(&world_transform, &camera, 50.0f);
	///m_UI_coordinates.Init_UI(&UI_transform, &camera, 0.1f);
	
	m_scene_manager.Init(&camera, &display);

	////////////////////////////////////////////////////////////////////////////////////////////////////


	while (!display.IsClosed())
	{	
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

		display.UpdateWindowSize();	// ȭ�� ����
		camera.Update(camera.GetPos(), 70.0f, display.GetWindowAspec(), 0.01F, 1000.0f);

		//display.Clear(0.1f, 0.1f, 0.1f, 1.0f);	// ��� �ʱ�ȭ
		//display.Clear(1.0f, 1.0f, 1.0f, 1.0f);	// ��� �ʱ�ȭ
		//display.Clear(0.3f, 0.3f, 0.3f, 1.0f);	// ��� �ʱ�ȭ

		//display.Clear(0.1f, 0.3f, 0.4f, 1.0f);	// ��� �ʱ�ȭ
		//display.Clear(0.0f / 255.0f, 76.0f / 255.0f, 176.0f / 255.0f, 1.0f);	// ��� �ʱ�ȭ

		//display.Clear(0.0f / 255.0f, 6.0f / 255.0f, 106.0f / 255.0f, 1.0f);	// ��� �ʱ�ȭ
		
		
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		// Draw here
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

		

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		
		//### �ó������� ��� ���
		printf("%c \n", controller.Get_curKey());
		m_scene_manager.Set_CurKey(controller.Get_curKey());
		m_scene_manager.Play();

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		
		// ���� ��ǥ�� �׸���
		//m_world_coordinates.Draw();

		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		
		
		display.Update();	// ȭ�鰻��
	}
}

#pragma once

#include "Display.h"
#include "ShapeManager.h"

#include "Coordinates.h"

#include "SceneManager.h"

namespace QuadCore
{


class Graphics_Simulator
{
public:
	Graphics_Simulator();
	virtual ~Graphics_Simulator();

	void Run();

private:
	const int  width_window = 640;	// 윈도우 창 (가로)
	const int height_window = 640;	// 윈도우 창 (세로)
	float aspec;					// 윈도우창 비율

	Display display;
	
	SceneManager m_scene_manager;

	Coordinates m_world_coordinates;
	Coordinates m_UI_coordinates;

	Camera camera;
	Transform world_transform;
};



}
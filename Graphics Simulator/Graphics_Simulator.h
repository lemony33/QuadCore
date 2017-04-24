#pragma once

#include "Display.h"
#include "ShapeManager.h"

#include "Coordinates.h"

#include "Scene.h"

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

	Display display;	
	
	Scene scene;

	Coordinates m_world_coordinates;
	Coordinates m_UI_coordinates;
};



}
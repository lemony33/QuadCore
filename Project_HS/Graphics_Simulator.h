#pragma once

#include "Display.h"



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
};



}
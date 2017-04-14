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
	const int  width_window = 640;	// ������ â (����)
	const int height_window = 640;	// ������ â (����)

	Display display;
};



}
#pragma once

#include "Display.h"
#include "ShapeManager.h"

namespace QuadCore
{
	class Graphics_Simulator
	{
	public:
		Graphics_Simulator();
		virtual ~Graphics_Simulator();

	public:
		void Run();

	private:
		Display display;
		ShapeManager m_shape_manager;
		const int  width_window = 640;	// 윈도우 창 (가로)
		const int height_window = 640;	// 윈도우 창 (세로)
	};
}
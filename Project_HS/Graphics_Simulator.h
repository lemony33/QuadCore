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
		const int  width_window = 640;	// ������ â (����)
		const int height_window = 640;	// ������ â (����)
	};
}